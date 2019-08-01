class HistoricalLayoutConfigurer {
    constructor() {
        this.container = null;
        this.nameInput = 'historicalLayoutNameInput';
        this.chartForm = new ChartForm();
        this.chartForm.addListener(this);
        this.charts = [];
        this.formControls = null;
        this.layout = null;
        this.dataShowed = false;
    }

    start() {
        this.container = $('#historicalCreationForm');
        $('#' + this.nameInput).on('input', (e) => this.formControls.setValue('name', e.currentTarget.value));
        this.chartForm.generate('historicalLayoutCharFormContainer');
        this.container.removeAttr('hidden');
        this.registerFormControls();
        $('#saveHistoricalConfigurationButton').on('click', () => this.validateAndSend());
        this.getInfos();
    }

    stop() {
        if (!this.container) {
            return;
        }
        this.container.attr('hidden', '');
        $('#historicalLayoutCharFormContainer').html('');
        $('#' + this.nameInput).off('input');
        $('#saveHistoricalConfigurationButton').off('click');

        const historicalData = $('#historicalData');
        historicalData.html('');
        historicalData.attr('hidden', '');
        this.dataShowed = false;
        this.layout = null;
    }

    getInfos() {
        historicConfigurationService.getList(configurations => {
            if (!configurations || !configurations.length || configurations.length < 1) {
                $('#layoutInfos').html(HistoricalLayoutInfo.generateEmpty());
                return;
            }
            console.log(configurations);
            const html = configurations.map(configuration => HistoricalLayoutInfo.generate(configuration)).join("<br />");
            $('#layoutInfos').html(html);
        });
    }

    validateAndSend() {
        if (this.formControls.isValid() === true) {
            const configuration = this.formControls.getValues();
            console.log(configuration);
            historicConfigurationService.post(configuration, (result) => {
                new Toast('success', 'Configuration saved').show();
                $('#historicalLayoutConfiguredChartsContainer').html('');
                this.getInfos();
            });
        }
    }

    addNewLayout() {
        if (this.dataShowed === true) {
            this.stop();
            this.start();
        }
    }


    registerFormControls() {
        this.formControls = new FormControls();
        this.formControls.add('name', '', (value) => value.match('^[\\w\\s]+$'), 'Please provide layout name', `historicalLayoutNameInputError`);
        this.formControls.addList('charts', [], (value) => value && value.length >= 1, 'Please add some series to chart', `historicalLayoutChartDataError`);
    }

    onNewChart(chartData) {
        console.log(chartData);
        this.formControls.pushToList('charts', chartData);
        if (this.formControls.getValue('charts').length > 0) {
            $('#historicalLayoutConfiguredChartsLabel').removeAttr('hidden');
            $('#saveHistoricalConfigurationButton').removeAttr('hidden');
        }
        const chartConfiguration = ConfiguredChartListBuilder.generate(chartData, guid());
        $('#historicalLayoutConfiguredChartsContainer').append(chartConfiguration);
    }

    onClickMakeInactiveConfiguration(uuid) {
        console.log(uuid);
        this.registerFormControls();
        historicConfigurationService.makeInactive(uuid, () => {console.log('getinfos');this.getInfos()});
    }

    onClickRemoveLayoutInfo(uuid) {
        if (!confirm('Do you really would like to remove this layout (all data will be lost)?')) {
            return;
        }
        historicConfigurationService.remove(uuid, (result) => {
            new Toast('success', 'Layout removed').show();
            this.getInfos();
        })
    }

    getData(uuid) {
        historicConfigurationService.get(uuid, (result) => {
            console.log(result);
            const historicalData = $('#historicalData');
            historicalData.html('');
            historicalData.removeAttr('hidden');
            $('#historicalCreationForm').attr('hidden', '');
            this.dataShowed = true;

            this.layout = new Layout('historicalData');
            result.charts.forEach(chartInfo => this.layout.addNewChartWithId(chartInfo, chartInfo.id, false));
            result.charts.forEach(chartInfo => {
                new Toast('info', 'getting data for:' + chartInfo.name + ' chart').show();
                historicConfigurationService.getData(uuid, chartInfo.id, (data) => {
                    const foundChat = this.layout.charts.find(chartItem => chartItem.id === chartInfo.id);
                    if (foundChat) {
                        foundChat.setLabels(data.labels);
                        data.series.forEach(dataSeries => this.setSeries(chartInfo, dataSeries, foundChat));
                    }
                });
            })
        });
    }

    setSeries(chartInfo, dataSeries, chart) {
        const chartInfoSeries = chartInfo.series.find(searchedSeries => searchedSeries.id === dataSeries.id);
        if (!chartInfoSeries) {
            console.log('series not found');
            return;
        }
        let values = [];
        if (dataSeries.values.length < 1) {
            return;
        }
        if (chartInfoSeries.dataType === dateType.hex) {
            values.push(0);
            for (let i = 1; i < dataSeries.values.length; i++) {
                let value = byteArrayToNumList(base64ToByteArray(dataSeries.values[i]))[0];
                if (chartInfoSeries.deltaValue === true) {
                    value -= byteArrayToNumList(base64ToByteArray(dataSeries.values[i - 1]))[0];
                }
                values.push(value);
            }
        } else if (chartInfoSeries.dataType === dateType.math) {
            values.push(0);
            for (let i = 1; i < dataSeries.values.length; i++) {
                let value = base64ToMathValue(dataSeries.values[i], chartInfoSeries.formula);
                if (chartInfoSeries.deltaValue === true) {
                    value -= base64ToMathValue(dataSeries.values[i -1], chartInfoSeries.formula);
                }
                values.push(value);
            }
        }
        console.log(values);
        chart.setSeries(dataSeries.id, values);
    }

}

class ConfiguredChartListBuilder {
    static generate(chartData, name) {
        const seriesDiv = chartData.series.map(serie => ConfiguredChartSeriesListBuilder.generate(serie, name)).join("\n");
        return `
        <div class="form-row align-items-center mb-2">
            <div class="col-xl-4">
                <label class="sr-only" for="${name}">Chart name</label>
                <input type="text" class="form-control" id="${name}" value="${chartData.name}" readonly>
        </div>
        <div class="col-xl-2">
                <label class="sr-only" for="${name}IntervalInput">Interval</label>
                <input type="text" class="form-control" id="${name}IntervalInput" value="${chartData.interval}" readonly>
            </div>
        </div>
        ${seriesDiv}
        <hr />`;
    }
}

class ConfiguredChartSeriesListBuilder {
    static generate(series, name) {
        const checked = series.deltaValue === true ? 'checked' : '';
        return `
            <div id="${name}_${series.id}" class="form-row align-items-center mt-2">
                <div class="col-md-1">
                    <label class="sr-only" for="${name}_${series.id}NameInput">Series name</label>
                    <input type="text" class="form-control" id="${name}_${series.id}NameInput_${series.id}" value="${series.name}" readonly>
                </div>
                <div class="col-md-1">
                    <label class="sr-only" for="${name}_${series.id}AddressInput_${series.id}">Address</label>
                    <input type="text" class="form-control" id="${name}_${series.id}AddressInput_${series.id}" value="${series.address}" readonly>
                </div>
                <div class="col-md-2">
                    <label class="sr-only" for="${name}_${series.id}DataTypeInput_${series.id}">Data type</label>
                    <input type="text" class="form-control" id="${name}_${series.id}DataTypeInput_${series.id}" value="${series.dataTypeValue}" readonly>
                </div>
                <div class="col-md-2">
                    <label class="sr-only" for="${name}_${series.id}FormulaInput_${series.id}">Formula</label>
                    <input type="text" class="form-control" id="${name}_${series.id}FormulaInput_${series.id}" value="${series.formula}" readonly>
                </div>
                <div class="col-xl-1" style="text-align: center">
                    <div class="custom-control custom-checkbox">
                        <input type="checkbox" class="custom-control-input" id="${name}_${series.id}DeltaValue_${series.id}">
                        <label class="custom-control-label" for="${name}DeltaValue_${series.id}" ${checked}>Calc delta with previous value</label>
                    </div>
                </div>
            </div>`;
    }
}

class HistoricalLayoutInfo {
    static generate(info) {
        const bg = info.isActive ? 'bg-light' : 'bg-dark';
        const colour = info.isActive ? '' : 'text-white';
        const isActiveText = info.isActive ? 'Active' : 'Inactive';
        const stopRecordingDataDiv = info.isActive ? HistoricalLayoutInfo.stopRecordingDataDiv(info) : '';
        return `
        <div class="card ${bg} ${colour} border-light h-100 mb-2" style="width: 27rem; cursor: pointer">
            <div class="card-body">
                <div class="row">
                    <div class="col-md-8" ">
                        <h5 class="card-title" onclick="historicalLayoutConfigurer.getData('${info.uuid}')" ">${info.name}(<code>${isActiveText}</code>)</h5>
                    </div>
                    <div class="col-md-4 text-right" style="cursor: pointer">
                        <span class="alert alert-danger" onclick="historicalLayoutConfigurer.onClickRemoveLayoutInfo('${info.uuid}')" title="Remove configuration"><i class="fa fa-times"></i></span>
                    </div>
                </div>
                <div class="row mt-3">
                    <div class="col-md-8" onclick="historicalLayoutConfigurer.getData('${info.uuid}')">
                        <p class="card-subtitle text-left">From: ${info.creationDate}</p>
                    </div>
                    ${stopRecordingDataDiv}
                </div>
                <div class="row mt-4">
                    <div class="col-md-8" onclick="historicalLayoutConfigurer.getData('${info.uuid}')">
                        <p class="card-subtitle text-left">To: ${info.toDate}</p>
                    </div>
                   
                </div>
            </div>
        </div>
        `;
    }

    static stopRecordingDataDiv(info) {
        return `
        <div class="col-md-4 text-right" style="cursor: pointer">
            <span class="alert alert-info" onclick="historicalLayoutConfigurer.onClickMakeInactiveConfiguration('${info.uuid}')" title="Stop recording data (make inactive)"><i class="fa fa-stop"></i></span>
        </div>
        `;
    }
    static generateEmpty() {
        return `
        <div class="row">
            <div class="col" ">
                No content available
            </div>
        </div>
        `;
    }

}