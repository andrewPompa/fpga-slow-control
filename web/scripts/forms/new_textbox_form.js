const newLayoutTextboxForm = new FormControls();


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
    newLayoutTextboxForm.add(
        'words',
        '',
        function (value) {
            const type = this.getParentForm().getValue('dataType');
            return !type || (type === dateType.hex && value.match('^[1-9]\\d*$')) || (type === dateType.math || type === dateType.date)
        },
        'Please provide num of words (grater than 0)',
        'newLayoutTextboxWordsInputError'
    );
    newLayoutTextboxForm.add('dataType', '', (value) => !!value, 'Please choose data type', 'newLayoutTextboxDataTypeError');
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

function clearNewLayoutTextboxForm() {
    $('#newLayoutTextboxItemNameInput').val('');
    $('#newLayoutTextboxAddressInput').val('');
    $('#newLayoutTextboxWordsInput').val('');
    $('#newLayoutTextboxDataType').html('Data type');
    $('#newLayoutTextboxFormulaInput').val('');
    $('#newLayoutTextBoxReadOnly').prop('checked', false);

    newLayoutTextboxForm.setValueNoValidate('name', '');
    newLayoutTextboxForm.setValueNoValidate('address', '');
    newLayoutTextboxForm.setValueNoValidate('words', '');
    newLayoutTextboxForm.setValueNoValidate('dataType', '');
    newLayoutTextboxForm.setValueNoValidate('formula', '');
    newLayoutTextboxForm.setValueNoValidate('readOnly', false);

    $('#inputsContainer').html('');
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

function newLayoutOnChangeRadioButton(e) {
    if (newLayoutTextboxRadio.id === e.target.id) {
        $("#newLayoutTextboxForm").removeAttr("hidden");
        $("#newLayoutChartForm").attr("hidden", 'hidden');
    } else if (newLayoutChartRadio.id === e.target.id) {
        $("#newLayoutTextboxForm").attr("hidden", 'hidden');
        $("#newLayoutChartForm").removeAttr("hidden");
    }
}

function validateAndSave(form) {
    if (form.isValid() === true) {
        const input = form.getValues();
        layout.addNewInput(input);
    }
}