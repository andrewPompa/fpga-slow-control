class HistoricalLayoutConfigurer {
    constructor() {
        this.container = null;
        this.nameInput = 'historicalLayoutNameInput';
        this.chartForm = new ChartForm();
        this.chartForm.addListener(this);
        this.charts = [];
        this.formControls = null;
    }

    start() {
        this.container = $('#historicalCreationForm');
        $('#' + this.nameInput).on('input', (e) => this.formControls.setValue('name', e.currentTarget.value));
        this.chartForm.generate('historicalLayoutCharFormContainer');
        this.container.removeAttr('hidden');
        this.registerFormControls();
        $('#saveHistoricalConfigurationButton').on('click', () => this.validateAndSend());
        historicConfigurationService.getList(configuration => {
            console.log(configuration);
        });
    }

    validateAndSend() {
        if (this.formControls.isValid() === true) {
            const configuration = this.formControls.getValues();
            console.log(configuration);
            historicConfigurationService.post(configuration, (result) => console.log(result));
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
        const chartConfiguration = ConfiguredChartListBuilder.generate(chartData, guid());
        $('#historicalLayoutConfiguredChartsContainer').append(chartConfiguration);
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
            </div>`;
    }
}

class HistoricalLayoutInfo {
    static generate() {
        return `
        `;
    }
}