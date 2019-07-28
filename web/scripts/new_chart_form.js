const newLayoutChartForm = new FormControls();

$(document).ready(() => {

    newLayoutChartForm.add('name', '', (value) => value.match('^[\\w\\s]+$'), 'Please provide item name', 'newLayoutChartItemNameInputError');
    newLayoutChartForm.add('address', '', (value) => value.match('^0x[A-Fa-f0-9]{1,8}$'), 'Please provide hexadecimal value (0x0 - 0xFFFFFFFF)', 'newLayoutChartAddressInputError');
    newLayoutChartForm.add('words', '', (value) => value.match('^[1-9]\\d*$'), 'Please provide num of words (grater than 0)', 'newLayoutChartWordsInputError');
    newLayoutChartForm.add('dataType', '', (value) => !!value, 'Please chose data type', 'newLayoutChartDateTypeError');
    newLayoutChartForm.add(
        'formula',
        '',
        function (value) {
            const v = this.getParentForm().getValue('dataType');
            return !v || (v === dateType.hex) || (v === dateType.math  && value.match('^.*x.*$'))
        },
        'Please provide formula which contains \'x\' variable',
        'newLayoutChartFormulaInputError'
    );
    newLayoutChartForm.add('interval', '', (value) => value.match("^\\d+$"), 'Please provide interval in millis', 'newLayoutChartIntervalInputError');

    newLayoutClearChartForm();
});

function newLayoutClearChartForm() {
    $('#newLayoutChartItemNameInput').val('');
    $('#newLayoutChartAddressInput').val('');
    $('#newLayoutChartWordsInput').val('');
    $('#newLayoutChartDateType').html('Data type');
    $('#newLayoutChartFormulaInput').val('');
    $('#newLayoutChartIntervalInput').val('');

    newLayoutChartForm.setValueNoValidate('name', '');
    newLayoutChartForm.setValueNoValidate('address', '');
    newLayoutChartForm.setValueNoValidate('words', '');
    newLayoutChartForm.setValueNoValidate('dataType', '');
    newLayoutChartForm.setValueNoValidate('formula', '');
    newLayoutChartForm.setValueNoValidate('interval', '');
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

function newLayoutValidateAndSaveChart() {
    if (newLayoutChartForm.isValid() === true) {
        const chartData = newLayoutChartForm.getValues();
        console.log(chartData);
        layout.addNewChart(chartData);
    }
}