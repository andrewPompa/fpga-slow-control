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
        () => {console.log(layout); return (layout.inputs && layout.inputs.length >= 1) || (layout.charts && layout.charts.length >= 1)},
        'Please add some items to layout',
        'invalidLayoutError'
    );
});

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
        configurationService.post(layoutObject, (result) => layoutInfoListAll());
    }
}