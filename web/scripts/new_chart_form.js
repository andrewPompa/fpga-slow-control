const newLayoutChartForm = new FormControls();
const newLayoutChartAddSeriesForm = new FormControls();

$(document).ready(() => {
    newLayoutChartForm.add('name', '', (value) => value.match('^[\\w\\s]+$'), 'Please provide item name', 'newLayoutChartNameInputError');
    newLayoutChartForm.add('interval', '', (value) => value.match("^\\d+$") && parseInt(value) >= 10, 'Please provide interval in millis (grater than 10 millis)', 'newLayoutChartIntervalInputError');
    newLayoutChartForm.addList('series', [], (value) => value && value.length >= 1, 'Please add some series to chart', 'newLayoutChartChartSaveButtonError');

    newLayoutChartAddSeriesForm.add(
        'name',
        '',
        (value) => {
            let nameExists = false;
            const s = newLayoutChartForm.getValue('series');
            if (s) {
                nameExists = !!s.find(control => control.name === value);
            }
            return value.match('^[\\w\\s]+$') && !nameExists;
        },
        'Series name not set or series with that name already exists',
        'newLayoutChartAddSeriesNameInputError'
    );
    newLayoutChartAddSeriesForm.add('address', '', (value) => value.match('^0x[A-Fa-f0-9]{1,8}$'), 'Please provide hexadecimal value (0x0 - 0xFFFFFFFF)', 'newLayoutChartAddSeriesAddressInputError');
    newLayoutChartAddSeriesForm.add('dataType', '', (value) => !!value, 'Please choose data type', 'newLayoutChartAddSeriesDataTypeError');
    newLayoutChartAddSeriesForm.add(
        'formula',
        '',
        function (value) {
            const v = this.getParentForm().getValue('dataType');
            return !v || (v === dateType.hex) || (v === dateType.math && value.match('^.*x.*$'))
        },
        'Please provide formula which contains \'x\' variable',
        'newLayoutChartAddSeriesFormulaInputError'
    );

    newLayoutClearChartForm();
});

function newLayoutClearChartForm() {
    $('#newLayoutChartNameInput').val('');
    $('#newLayoutChartIntervalInput').val('');

    $('#newLayoutChartAddSeriesNameInput').val('');
    $('#newLayoutChartAddSeriesAddressInput').val('');
    $('#newLayoutChartAddSeriesDataType').html('Data type');
    $('#newLayoutChartAddSeriesFormulaInput').val('');
    $("#newLayoutSeriesContainer").html('');


    newLayoutChartForm.setValueNoValidate('name', '');
    newLayoutChartForm.setValueNoValidate('interval', '');
    newLayoutChartForm.setValueNoValidate('series', []);

    newLayoutChartAddSeriesForm.setValueNoValidate('name', '');
    newLayoutChartAddSeriesForm.setValueNoValidate('address', '');
    newLayoutChartAddSeriesForm.setValueNoValidate('dataType', '');
    newLayoutChartAddSeriesForm.setValueNoValidate('formula', '');

}

function onChangeDateTypeForChart(form, value, label, formulaInputName, menuButton) {
    form.setValue('dataType', value);
    const formula = $("#" + formulaInputName);
    $('#' + menuButton).html(label);

    if (value === dateType.hex) {
        formula.attr("disabled", "");
    } else if (value === dateType.math) {
        formula.removeAttr("disabled");
    }
    form.checkValidity(form.get('formula'));

}

function newLayoutValidateAddSeries() {
    if (newLayoutChartAddSeriesForm.isValid() === true) {
        const series = newLayoutChartAddSeriesForm.getValues();
        newLayoutChartForm.pushToList('series', series);

        series.dataTypeValue = (series.dataType === dateType.hex) ? 'Hexadecimal value' : 'Mathematical value';
        const seriesDiv = new NewChartSeriesBuilder(series).generate();
        $("#newLayoutSeriesContainer").append(seriesDiv);
    }
}

function newLayoutRemoveSeries(id) {
    const series = newLayoutChartForm.findInList('series', id);
    if (!series) {
        return;
    }
    $("#newLayoutSeries_" + id).remove();
    newLayoutChartForm.removeFromList('series', id)
}

function newLayoutValidateAndSaveChart() {
    if (newLayoutChartForm.isValid() === true) {
        const chartData = newLayoutChartForm.getValues();
        layout.addNewChart(chartData);
        newLayoutClearChartForm();
    }
}

class NewChartSeriesBuilder {
    constructor(series) {
        this.series = series;
    }

    generate() {
        return `
            <div id="newLayoutSeries_${this.series.id}" class="form-row align-items-center mt-2">
                <div class="col-md-1">
                    <label class="sr-only" for="newLayoutChartSeriesNameInput_${this.series.id}">Series name</label>
                    <input type="text" class="form-control" id="newLayoutChartSeriesNameInput_${this.series.id}" value="${this.series.name}" readonly>
                </div>
                <div class="col-md-1">
                    <label class="sr-only" for="newLayoutChartSeriesAddressInput_${this.series.id}">Address</label>
                    <input type="text" class="form-control" id="newLayoutChartSeriesAddressInput_${this.series.id}" value="${this.series.address}" readonly>
                </div>
                <div class="col-md-2">
                    <label class="sr-only" for="newLayoutChartSeriesDataTypeInput_${this.series.id}">Data type</label>
                    <input type="text" class="form-control" id="newLayoutChartSeriesDataTypeInput_${this.series.id}" value="${this.series.dataTypeValue}" readonly>
                </div>
                <div class="col-md-2">
                    <label class="sr-only" for="newLayoutChartSeriesFormulaInput_${this.series.id}">Formula</label>
                    <input type="text" class="form-control" id="newLayoutChartSeriesFormulaInput_${this.series.id}" value="${this.series.formula}" readonly>
                </div>
                <div class="col-md-1">
                    <button type="button" class="btn w-100 btn-danger" onclick="newLayoutRemoveSeries(${this.series.id})">Delete series <span><i class="fa fa-times"></i></span></button>
                </div>
            </div>`;
    }
}