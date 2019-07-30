const dateType = {
    date: 'date',
    math: 'math',
    hex: 'hex'
};

$(document).ready(function () {
    newLayout.add('name', '', (value) => value.match('^[\\w\\s]+$'), 'Please insert layout name', 'layoutNameInputError');
    newLayout.addList(
        'controls',
        [],
        () => (layout.inputs && layout.inputs.length >= 1) || (layout.charts && layout.charts.length >= 1),
        'Please add some items to layout',
        'invalidLayoutError'
    );
    layoutReset();
});

function layoutSetName(name)  {
    newLayout.setValue('name', name);
    $('#layoutNameInput').val(name);

}

function layoutReset() {
    $('#layoutNameInput').val('');

    layout.charts.forEach(chart => chart.removeInterval());
    layout = new Layout();

    newLayout.setValueNoValidate('name', '');
    newLayout.setValueNoValidate('controls', []);
}

function validateAndSaveLayout() {
    if (newLayout.isValid()) {
        const layoutObject = {name: newLayout.getValue('name'), controls: {inputs: layout.getInputs(), charts: layout.getCharts()}};
        if (layout.uuid) {
            configurationService.put(layout.uuid, layoutObject, () => {
                new Toast('success', 'Layout updated').show();
                layoutInfoListAll();
            });
        } else {
            configurationService.post(layoutObject, () => {
                new Toast('success', 'Layout created').show();
                layoutInfoListAll();
            });
        }
    }
}