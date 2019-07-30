let configurationService = new ConfigurationService();
let wordService = new WordsService();
let newLayoutTextboxRadio;
let newLayoutChartRadio;
let newLayout = new FormControls();
let layout = new Layout();
let persistedLayout = null;
let currentDataButton;
let historicalLayoutConfigurer = new HistoricalLayoutConfigurer();
let historicConfigurationService = new HistoricConfigurationService();

$(document).ready(() => {
    currentDataButton = $('#currentDataButton');
    currentDataButton.click();
    resetCurrentLayout();
});

function resetCurrentLayout() {
    layoutReset();
    newLayoutClearChartForm();
    clearNewLayoutTextboxForm();
}

function layoutInfoListAll() {
    configurationService.getList((configurations) => {
        let html = '';
        if (!configurations || !configurations.length || configurations.length < 1) {
            html = `<div class="row  "><div class="col-auto text-center align-middle">No content available</div></div>`
        } else {
            html = configurations.map(configuration => layoutInfoToHtml(configuration)).join("\n");
        }
        $('#layoutInfos').html(html);
    });
}

function loadLayout(uuid) {
    configurationService.get(uuid, (configuration) => {
        resetCurrentLayout();
        persistedLayout = new Layout();
        persistedLayout.uuid = uuid;
        persistedLayout.name = configuration.name;

        layout.uuid = uuid;
        layout.name = configuration.name;
        layoutSetName(configuration.name);
        configuration.controls.inputs.forEach(input => layout.addNewInput(input));
        configuration.controls.charts.forEach(chart => layout.addNewChart(chart));

        persistedLayout.inputs = [...layout.inputs];
        persistedLayout.charts = [...layout.charts];
        console.log(persistedLayout);
    });
    console.log('loading layout' + uuid);
}

function removeLayout(uuid) {
    console.log('removing layout ' + uuid);
    if (!confirm('Do you really want to remove this layout?')) {
        return;
    }
    configurationService.remove(uuid, () => {
        new Toast('info', 'Layout deleted').show();
        resetCurrentLayout();
        layoutInfoListAll();
    });
}


function onClickCurrentDataButton() {
    $('#historicalDataButton').removeClass("active");
    $('#activeLayoutViewContainer').removeAttr('hidden');
    currentDataButton.addClass("active");
    // layoutInfoListAll();

}

function onClickHistoricalDataButton() {
    if (isActiveLayoutChanged()) {
        if (!confirm('Edited layout is changed, would you like to update it?')) {
            return;
        }
        validateAndSaveLayout();
    }
    resetCurrentLayout();
    currentDataButton.removeClass("active");
    $('#historicalDataButton').addClass("active");
    $('#activeLayoutViewContainer').attr('hidden', '');
    historicalLayoutConfigurer.start();


}

function onAddNewLayout() {
    if (isActiveLayoutChanged()) {
        if (!confirm('Edited layout is changed, would you like to update it?')) {
            return;
        }
        validateAndSaveLayout();
    }
    resetCurrentLayout();
}

function isActiveLayoutChanged() {
    const layoutObject = {name: newLayout.getValue('name'), controls: {inputs: layout.getInputs(), charts: layout.getCharts()}};
    if (!persistedLayout && layoutObject.name === '' && layoutObject.controls.inputs.length === 0 && layoutObject.controls.charts.length === 0) {
        return false;
    } else if (!persistedLayout) {
        return true;
    }
    const persistedLayoutObject = {name: persistedLayout.name, controls: {inputs: persistedLayout.getInputs(), charts: persistedLayout.getCharts()}};
    return layout.uuid && JSON.stringify(layoutObject) !== JSON.stringify(persistedLayoutObject);
}


function layoutInfoToHtml(configuration) {
    return `<div class="card border-light bg-light h-100 mb-2" style="width: 20rem; cursor: pointer">
        <div class="card-body">
            <div class="row">
                <div class="col-md-8" onclick="loadLayout('${configuration.uuid}')">
                    <h5 class="card-title">${configuration.name}</h5>
                </div>
                <div class="col-md-4 text-right" style="cursor: pointer" onclick="removeLayout('${configuration.uuid}')">
                    <span class="alert alert-danger"><i class="fa fa-times"></i></span>
                 </div>
            </div>
            <div class="row mt-2" onclick="loadLayout('${configuration.uuid}')">
                <div class="col-md-12">
                    <p class="card-subtitle text-left">Created: ${layoutInfoPrepareDate(configuration.creationDate)}</p>
                </div>
            </div>
        </div>
    </div>`
}

function layoutInfoPrepareDate(creationDate) {
    return creationDate.substr(0, 4) + "-" + creationDate.substr(4, 2) + "-" + creationDate.substring(6);
}