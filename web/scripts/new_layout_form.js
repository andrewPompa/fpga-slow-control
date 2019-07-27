const dateType = {
    date: 'date',
    math: 'math',
    hex: 'hex'
};

let newLayoutTextboxRadio;
let newLayoutChartRadio;

const newLayoutTextboxForm = new FormControls();
const newLayoutChartForm = new FormControls();

$(document).ready(() => {
    $("input[type=radio][name=radio-stacked]").change(newLayoutOnChangeRadioButton);
    newLayoutTextboxRadio = $("#newLayoutTextboxRadio")[0];
    newLayoutChartRadio = $("#newLayoutChartRadio")[0];

    const selectedRadioButton = $("input[type=radio][name=radio-stacked]:checked")[0];
    if (selectedRadioButton) {
        newLayoutOnChangeRadioButton({target: selectedRadioButton});
    } else {
        newLayoutTextboxRadio.checked = true;
        newLayoutOnChangeRadioButton({target: newLayoutTextboxRadio});
    }

    newLayoutTextboxForm.add('name', '', (value) => value.match('^[\\w\\s]+$'), 'Please provide item name', 'newLayoutTextboxItemNameInputError');
    newLayoutTextboxForm.add('address', '', (value) => value.match('^0x[A-Fa-f0-9]{1,8}$'), 'Please provide hexadecimal value (0x0 - 0xFFFFFFFF)', 'newLayoutTextboxAddressInputError');
    newLayoutTextboxForm.add('words', '', (value) => value.match('^[1-9]\\d*$'), 'Please provide num of words (grater than 0)', 'newLayoutTextboxWordsInputError');
    newLayoutTextboxForm.add('dataType', '', (value) => !!value, 'Please chose data type', 'newLayoutTextboxDataTypeError');
    newLayoutTextboxForm.add(
        'formula',
        '',
        function (value) {
            const v = this.getParentForm().getValue('dataType');
            return !v || (v === dateType.hex || v === dateType.date) || (v === dateType.math  && value.match('^.*x.*$'))
        },
        'Please provide formula which contains \'x\' variable',
        'newLayoutTextboxFormulaInputError'
    );
    newLayoutTextboxForm.add('readOnly', false, () => true, '', null);

    newLayoutChartForm.add('name', '', (value) => value.match('^[\\w\\s]+$'), 'Please provide item name', 'newLayoutChartItemNameInputError');
    newLayoutChartForm.add('address', '', (value) => value.match('^0x[A-Fa-f0-9]{1,8}$'), 'Please provide hexadecimal value (0x0 - 0xFFFFFFFF)', 'newLayoutChartAddressInputError');
    newLayoutChartForm.add('words', '', (value) => value.match('^[1-9]\\d*$'), 'Please provide num of words (grater than 0)', 'newLayoutChartWordsInputError');
    newLayoutChartForm.add('dataType', '', (value) => !!value, 'Please chose data type', 'newLayoutChartDateTypeError');
    newLayoutChartForm.add(
        'formula',
        '',
        (value) => {
            const v = this.getParentForm().getValue('dataType');
            return (v === dateType.hex) || (v === dateType.math  && value.match('^.*x.*$'))
        },
        'Please provide formula which contains \'x\' variable',
        'chartFormulaInputError'
    );
    newLayoutChartForm.add('interval', '', (value) => value.match("^\\d+$"), 'Please provide interval in millis', 'newLayoutChartIntervalInputError');
});


function onChangeDateType(form, value, label, formulaInputName, menuButton) {
    form.setValue('dataType', value);
    form.checkValidity(form.get('formula'));
    const formula = $("#" + formulaInputName);
    $('#' + menuButton).html(label);
    if (value === dateType.date || value === dateType.hex) {
        formula.attr("disabled", "");
    } else if (value === dateType.math) {
        formula.removeAttr("disabled");
    }
}

function newLayoutOnChangeRadioButton(e) {
    console.log(e.target.id);
    if (newLayoutTextboxRadio.id === e.target.id) {
        $("#newLayoutTextboxForm").removeAttr("hidden");
        $("#newLayoutChartForm").attr("hidden", 'hidden');
        // newItem = {name: '', address: -1, words: -1, type: null, formula: '', readOnly: false};
    } else if (newLayoutChartRadio.id === e.target.id) {
        $("#newLayoutTextboxForm").attr("hidden", 'hidden');
        $("#newLayoutChartForm").removeAttr("hidden");

        // newItem = {name: '', address: -1, words: -1, type: null, formula: '', interval: -1};
    }
}

function validateAndSave(form) {
    form.validateAll();
}

function newLayoutValidate() {
}
