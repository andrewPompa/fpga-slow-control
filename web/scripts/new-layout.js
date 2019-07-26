const dateType = {
    date: 'date',
    math: 'math',
    hex: 'hex'
};

let newLayoutTextboxRadio;
let newLayoutChartRadio;
let newLayoutTextboxForm;
let newLayoutChartForm;

let newItem = {};

let formControls = [
    {id: 'inputName', value: '', isValid: (value) => value.match('^\\w+$'), errorMessage: 'Please provide item name', errorDiv: 'itemNameInputError'},
    {id: 'address', value: '', isValid: (value) => value.match('^0x[A-Fa-f0-9]{1,8}$'), errorMessage: 'Please provide hexadecimal value (0x0 - 0xFFFFFFFF)', errorDiv: 'addressInputError'},
    {id: 'words', value: '', isValid: (value) => value.match('^[1-9]\\d*$'), errorMessage: 'Please provide num of words (grater than 0)', errorDiv: 'wordsInputError'},
    {id: 'type', isValid: (value) => !!value, errorMessage: 'Please chose data type', value: null, errorDiv: 'newInputDateTypeMenuError'},
    {
        id: 'formula',
        value: '',
        isValid: (value) => !formControls.find(f => f.id === 'type') || formControls.find(f => f.id === 'type').value !== dateType.math || formControls.find(f => f.id === 'type').value === dateType.math  && value.match('^.*x.*$'),
        errorMessage: 'Please provide formula which contains \'x\' variable',
        errorDiv: 'textboxFormulaInputError'
    },
];

$(document).ready(() => {
    $("input[type=radio][name=radio-stacked]").change(newLayoutOnChangeRadioButton);
    newLayoutTextboxRadio = $("#newLayoutTextboxRadio")[0];
    newLayoutChartRadio = $("#newLayoutChartRadio")[0];
    newLayoutTextboxForm = $("#newLayoutTextboxForm")[0];
    newLayoutChartForm = $("#newLayoutChartForm")[0];

    const selectedRadioButton = $("input[type=radio][name=radio-stacked]:checked")[0];
    if (selectedRadioButton) {
        newLayoutOnChangeRadioButton({target: selectedRadioButton});
    } else {
        newLayoutTextboxRadio.checked = true;
        newLayoutOnChangeRadioButton({target: newLayoutTextboxRadio});
    }
});

function setNewItemValue(id, value) {
    let formControl = formControls.find(item => item.id === id);
    if (formControl) {
        formControl.value = value;
        checkValidity(formControl);
    }
}

function onChangeDateType(value, label, formulaInputName) {
    setNewItemValue('type', value);
    $('#newInputDateTypeMenu').html(label);

    const formula = $("#" + formulaInputName);
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
        newItem = {name: '', address: -1, words: -1, type: null, formula: '', readOnly: false};
    } else if (newLayoutChartRadio.id === e.target.id) {
        $("#newLayoutTextboxForm").attr("hidden", 'hidden');
        $("#newLayoutChartForm").removeAttr("hidden");

        newItem = {name: '', address: -1, words: -1, type: null, formula: '', interval: -1};
    }
}

function newLayoutValidateAndSaveTextBox() {
    const address = $("#addressInput");
    newLayoutValidate();
}

function newLayoutValidate() {
    formControls.forEach(formControl => checkValidity(formControl));
}

function checkValidity(formControl) {
    if (!formControl.isValid) {
        return;
    }
    const errorControl = $(`#${formControl.errorDiv}`);
    if (!formControl.isValid(formControl.value)) {
        console.log('not match');
        errorControl.css("display", "block");
        errorControl.html(formControl.errorMessage);
    } else {
        console.log('match');
        errorControl.css("display", "none");
        errorControl.html('');
    }
}
