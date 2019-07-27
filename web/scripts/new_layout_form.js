const dateType = {
    date: 'date',
    math: 'math',
    hex: 'hex'
};

let wordService = new WordsService();
let newLayoutTextboxRadio;
let newLayoutChartRadio;
let layout = new Layout('inputsContainer');

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

    newLayoutTextboxForm.add('name', 'Test', (value) => value.match('^[\\w\\s]+$'), 'Please provide item name', 'newLayoutTextboxItemNameInputError');
    newLayoutTextboxForm.add('address', '0xAABBCCDD', (value) => value.match('^0x[A-Fa-f0-9]{1,8}$'), 'Please provide hexadecimal value (0x0 - 0xFFFFFFFF)', 'newLayoutTextboxAddressInputError');
    newLayoutTextboxForm.add(
        'words',
        '4',
        function (value) {
            const type = this.getParentForm().getValue('dataType');
            return (type === dateType.hex && value.match('^[1-9]\\d*$')) || (type === dateType.math || type === dateType.date)
        },
        'Please provide num of words (grater than 0)',
        'newLayoutTextboxWordsInputError'
    );
    newLayoutTextboxForm.add('dataType', 'hex', (value) => !!value, 'Please chose data type', 'newLayoutTextboxDataTypeError');
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


function onChangeDateTypeForInput(form, value, label, wordsInputName, formulaInputName, menuButton) {
    form.setValue('dataType', value);
    const formula = $("#" + formulaInputName);
    const words = $("#" + wordsInputName);
    const readOnly = $('#newLayoutTextBoxReadOnly');

    $('#' + menuButton).html(label);

    if (value === dateType.hex) {
        formula.attr("disabled", "");
        words.removeAttr("disabled");
        readOnly.removeAttr("disabled");
    } else if (value === dateType.math) {
        formula.removeAttr("disabled");
        words.attr("disabled", "");
        words.val(1);
        form.setValue('words', '1');

        readOnly.prop('checked', true);
        readOnly.attr('disabled', '');
        form.setValue('readOnly', true);
    } else if (value === dateType.date) {
        formula.attr("disabled", "");
        words.attr("disabled", "");
        words.val(1);
        form.setValue('words', '1');

        readOnly.prop('checked', true);
        readOnly.attr('disabled', '');
        form.setValue('readOnly', true);
    }

    form.checkValidity(form.get('formula'));
    form.checkValidity(form.get('words'));

}

function newLayoutChangeReadOnly() {
    newLayoutTextboxForm.setValue('readOnly', $('#newLayoutTextBoxReadOnly')[0].checked);
}

function newLayoutSetTextboxWordsChanged(value) {
    const readOnly = $('#newLayoutTextBoxReadOnly');
    newLayoutTextboxForm.setValue('words', value);
    if (newLayoutTextboxForm.getValue('dataType') === dateType.hex && newLayoutTextboxForm.getValue('words') !== '1') {
        readOnly.prop('checked', true);
        readOnly.attr('disabled', '');
    } else {
        readOnly.removeAttr('disabled', '');
    }
}

function onChangeDateTypeForChart(form, value, label, wordsInputName, formulaInputName, menuButton) {
    form.setValue('dataType', value);
    const formula = $("#" + formulaInputName);
    const words = $("#" + wordsInputName);
    $('#' + menuButton).html(label);

    if (value === dateType.hex) {
        formula.attr("disabled", "");
    } else if (value === dateType.math) {
        formula.removeAttr("disabled");
    } else if (value === dateType.math) {
        formula.removeAttr("disabled");
    }
    // if (value !== dateType.) {
    //     words.attr("disabled", "");
    // } else {
    //     words.removeAttr("disabled");
    // }

    form.checkValidity(form.get('formula'));
    form.checkValidity(form.get('words'));

}

function newLayoutOnChangeRadioButton(e) {
    console.log(e.target.id);
    if (newLayoutTextboxRadio.id === e.target.id) {
        $("#newLayoutTextboxForm").removeAttr("hidden");
        $("#newLayoutChartForm").attr("hidden", 'hidden');
    } else if (newLayoutChartRadio.id === e.target.id) {
        $("#newLayoutTextboxForm").attr("hidden", 'hidden');
        $("#newLayoutChartForm").removeAttr("hidden");

        // newItem = {name: '', address: -1, words: -1, type: null, formula: '', interval: -1};
    }
}

function validateAndSave(form) {
    if (form.isValid() === true) {
        const input = form.getInput();
        console.log(input);
        layout.addNewInput(input);
    }
}

function newLayoutValidate() {
}
