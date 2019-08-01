class ChartForm {
    constructor() {
        this.name = guid();
        this.formControls = null;
        this.seriesFormControls = null;
        this.listeners = [];
    }

    addListener(listener) {
        this.listeners.push(listener);
    }

    generate(container) {
        const chart = ChartFormBuilder.generate(this.name);
        $('#' + container).html(chart);
        this.registerInputs();
        this.clearForm();
    }

    setFormControls() {
        this.formControls = new FormControls();
        this.formControls.add('name', '', (value) => value.match('^[\\w\\s]+$'), 'Please provide item name', `${this.name}Error`);
        this.formControls.add('interval', '', (value) => value.match("^\\d+$") && parseInt(value) >= 10, 'Please provide interval in millis (grater than 10 millis)', `${this.name}IntervalInputError`);
        this.formControls.addList('series', [], (value) => value && value.length >= 1, 'Please add some series to chart', `${this.name}AddChartButtonError`);
    }
    setSeriesFormControls() {
        this.seriesFormControls = new FormControls();
        this.seriesFormControls.add(
            'name',
            '',
            (value) => {
                let nameExists = false;
                const s = this.formControls.getValue('series');
                if (s) {
                    nameExists = !!s.find(control => control.name === value);
                }
                return value.match('^[\\w\\s]+$') && !nameExists;
            },
            'Series name not set or series with that name already exists',
            `${this.name}SeriesNameInputError`
        );
        this.seriesFormControls.add('address', '', (value) => value.match('^0x[A-Fa-f0-9]{1,8}$'), 'Please provide hexadecimal value (0x0 - 0xFFFFFFFF)', `${this.name}AddressInputError`);
        this.seriesFormControls.add('dataType', '', (value) => !!value, 'Please choose data type', `${this.name}AddSeriesDataTypeError`);
        this.seriesFormControls.add(
            'formula',
            '',
            function (value) {
                const v = this.getParentForm().getValue('dataType');
                return !v || (v === dateType.hex) || (v === dateType.math && value.match('^.*x.*$'))
            },
            'Please provide formula which contains \'x\' variable',
            `${this.name}AddSeriesFormulaInputError`
        );
        this.seriesFormControls.add('deltaValue', false, (value) => true, '', '');
    }

    registerInputs() {
        $(`#${this.name}`).on('input', (e) => this.formControls.setValue('name', e.currentTarget.value));
        $(`#${this.name}IntervalInput`).on('input', (e) => this.formControls.setValue('interval', e.currentTarget.value));
        $(`#${this.name}NameInput`).on('input', (e) => this.seriesFormControls.setValue('name', e.currentTarget.value));
        $(`#${this.name}AddressInput`).on('input', (e) => this.seriesFormControls.setValue('address', e.currentTarget.value));
        $(`#${this.name}DeltaValue`).on('change', (e) => {console.log(e.currentTarget.checked); this.seriesFormControls.setValue('deltaValue', e.currentTarget.checked)});
        $(`#${this.name}AddSeriesFormulaInput`).on('input', (e) => this.seriesFormControls.setValue('formula', e.currentTarget.value));

        $(`#${this.name}HexButton`).on('click', () => this.onChangeDateTypeForChart(dateType.hex, 'Hexadecimal value'));
        $(`#${this.name}MathButton`).on('click', () => this.onChangeDateTypeForChart(dateType.math, 'Mathematical formula'));
        $(`#${this.name}AddSeriesButton`).on('click', () => this.validateAddSeries());
        $(`#${this.name}AddChartButton`).on('click', () => this.validateAndSaveChart());
        $(`#${this.name}ClearChartButton`).on('click', () => this.clearForm());
    }

    onChangeDateTypeForChart(value, label) {
        this.seriesFormControls.setValue('dataType', value);
        const formula = $(`#${this.name}AddSeriesFormulaInput`);
        $(`#${this.name}AddSeriesDataType`).html(label);

        if (value === dateType.hex) {
            formula.attr("disabled", "");
        } else if (value === dateType.math) {
            formula.removeAttr("disabled");
        }
        this.seriesFormControls.checkValidity(this.seriesFormControls.get('formula'));

    }

    clearForm() {
        $(`#${this.name}`).val('');
        $(`#${this.name}IntervalInput`).val('');
        $(`#${this.name}SeriesContainer`).html('');
        this.setFormControls();
        this.clearSeries();
    }

    clearSeries() {
        $(`#${this.name}NameInput`).val('');
        $(`#${this.name}AddressInput`).val('');
        $(`#${this.name}AddSeriesDataType`).html('Data type');
        $(`#${this.name}AddSeriesFormulaInput`).val('');

        this.setSeriesFormControls();
    }

    validateAddSeries() {
        console.log(this.seriesFormControls);
        if (this.seriesFormControls.isValid() === true) {
            const series = this.seriesFormControls.getValues();
            this.formControls.pushToList('series', series);

            series.dataTypeValue = (series.dataType === dateType.hex) ? 'Hexadecimal value' : 'Mathematical value';
            const seriesDiv = ChartSeriesBuilder.generate(series, this.name);
            console.log('before');
            $(`#${this.name}SeriesContainer`).append(seriesDiv);
            console.log('after');
            $(`#${series.id}DeleteSeries`).on('click', () => this.deleteSeries(series.id));
            this.clearSeries();
        }
    }

    validateAndSaveChart() {
        if (this.formControls.isValid() === true) {
            const chartData = this.formControls.getValues();
            this.clearForm();
            this.listeners.forEach(listener => listener.onNewChart(chartData));
        }
    }

    deleteSeries(id) {
        const series = this.formControls.findInList('series', id);
        if (!series) {
            return;
        }
        $(`#${this.name}_${id}`).remove();
        this.formControls.removeFromList('series', id)
    }
}

class ChartFormBuilder {
    static generate(name) {
        return `
        <div class="form-row align-items-center">
            <div class="col-xl-4">
                <label class="sr-only" for="${name}">Chart name</label>
                <input type="text" class="form-control" id="${name}" placeholder="Chart name">
                <div id="${name}Error" class="invalid-tooltip"></div>
            </div>
            <div class="col-xl-2">
                <label class="sr-only" for="${name}IntervalInput">Interval</label>
                <input type="text" class="form-control" id="${name}IntervalInput" placeholder="Interval">
                <div id="${name}IntervalInputError" class="invalid-tooltip"></div>
            </div>
        </div>
        <div id="${name}SeriesContainer"></div>
        <div class="form-row align-items-center mt-2">
            <div class="col-xl-1">
                <label class="sr-only" for="${name}NameInput">Series name</label>
                <input type="text" class="form-control" id="${name}NameInput" placeholder="Series name">
                <div id="${name}SeriesNameInputError" class="invalid-tooltip"></div>
            </div>
            <div class="col-xl-1">
                <label class="sr-only" for="${name}AddressInput">Address</label>
                <input type="text" class="form-control" id="${name}AddressInput" placeholder="Hex address">
                <div id="${name}AddressInputError" class="invalid-tooltip"></div>
            </div>
            <div class="col-xl-2 dropdown">
                <button class="btn btn-primary dropdown-toggle w-100" type="button" id="${name}AddSeriesDataType" data-toggle="dropdown" aria-haspopup="true"
                        aria-expanded="false">
                    Data type
                </button>
                <div class="dropdown-menu">
                    <a id="${name}HexButton" class="dropdown-item">
                        Hexadecimal value
                    </a>
                    <a id="${name}MathButton" class="dropdown-item">
                        Mathematical formula
                    </a>
                </div>
                <div id="${name}AddSeriesDataTypeError" class="invalid-tooltip"></div>
            </div>
            <div class="col-xl-1" style="text-align: center">
                <div class="custom-control custom-checkbox">
                    <input type="checkbox" class="custom-control-input" id="${name}DeltaValue">
                    <label class="custom-control-label" for="${name}DeltaValue">Calc delta with previous value</label>
                </div>
            </div>
            <div class="col-xl-2">
                <label class="sr-only" for="{name}AddSeriesFormulaInput">Formula</label>
                <input type="text" class="form-control" id="${name}AddSeriesFormulaInput" placeholder="Formula">
                <div id="${name}AddSeriesFormulaInputError" class="invalid-tooltip"></div>
            </div>
            <div class="col-xl-1">
                <button id="${name}AddSeriesButton" type="button" class="btn w-100 btn-success" >Add series <span><i class="fa fa-check"></i></span></button>
            </div>
        </div>
        <div class="form-row align-items-center mt-2">
            <div class="col-xl-2">
                <button id="${name}AddChartButton" type="button" class="btn w-100 btn-success" >Add new chart <span><i class="fa fa-area-chart"></i></span>
                </button>
                <div id="${name}AddChartButtonError" class="invalid-tooltip"></div>
            </div>
            <div class="col-xl-2">
                <button id="${name}ClearChartButton" type="button" class="btn w-100 btn-secondary" >Clear form <span><i class="fa fa-trash"></i></span></button>
            </div>
        </div>
        `;
    }
}

class ChartSeriesBuilder {
    static generate(series, name) {
        const checked = series.deltaValue === true ? 'checked' : '';
        return `
            <div id="${name}_${series.id}" class="form-row align-items-center mt-2">
                <div class="col-xl-1">
                    <label class="sr-only" for="${name}_${series.id}NameInput">Series name</label>
                    <input type="text" class="form-control" id="${name}_${series.id}NameInput_${series.id}" value="${series.name}" readonly>
                </div>
                <div class="col-xl-1">
                    <label class="sr-only" for="${name}_${series.id}AddressInput_${series.id}">Address</label>
                    <input type="text" class="form-control" id="${name}_${series.id}AddressInput_${series.id}" value="${series.address}" readonly>
                </div>
                <div class="col-xl-2">
                    <label class="sr-only" for="${name}_${series.id}DataTypeInput_${series.id}">Data type</label>
                    <input type="text" class="form-control" id="${name}_${series.id}DataTypeInput_${series.id}" value="${series.dataTypeValue}" readonly>
                </div>
                <div class="col-xl-2">
                    <label class="sr-only" for="${name}_${series.id}FormulaInput_${series.id}">Formula</label>
                    <input type="text" class="form-control" id="${name}_${series.id}FormulaInput_${series.id}" value="${series.formula}" readonly>
                </div>
                <div class="col-xl-1" style="text-align: center">
                    <div class="custom-control custom-checkbox">
                        <input type="checkbox" class="custom-control-input" id="${name}DeltaValue_${series.id}" ${checked} readonly>
                        <label class="custom-control-label" for="${name}DeltaValue_${series.id}">Calc delta with previous value</label>
                    </div>
                </div>
                <div class="col-xl-1">
                    <button type="button" id="${series.id}DeleteSeries" class="btn w-100 btn-danger">Delete series <span><i class="fa fa-times"></i></span></button>
                </div>
            </div>`;
    }
}