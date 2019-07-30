let configurationService = new ConfigurationService();
let wordService = new WordsService();
let newLayoutTextboxRadio;
let newLayoutChartRadio;
let newLayout = new FormControls();
let layout = new Layout();

let selectLayout;
let currentDataButton;
let currentLayouts = [];

$(document).ready(() => {
    selectLayout = $('#selectForm');
    currentDataButton = $('#currentDataButton');
    currentDataButton.click();
    layoutInfoListAll();
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
        layout.uuid = uuid;
        layout.name = configuration.name;
        configuration.controls.inputs.forEach(input => layout.addNewInput(input));
        configuration.controls.charts.forEach(chart => layout.addNewChart(chart));
    });
    console.log('loading layout' + uuid);
}

function removeLayout(uuid) {
    console.log('removing layout ' + uuid);
    if (!confirm('Do you really want to remove this layout?')) {
        return;
    }
    configurationService.remove(uuid, () => {
        layoutInfoListAll()
    });
}


function onClickCurrentDataButton() {
    $('#historicalDataButton').removeClass("active");
    currentDataButton.addClass("active");
    selectLayout.removeAttr('hidden');

    const currentLayouts = getCurrentLayouts();
    if (currentLayouts.length !== 0) {
        generateOptions(currentLayouts);
    } else {
        selectLayout.attr('hidden', 'hidden');
    }
}

function onClickHistoricalDataButton() {
    currentDataButton.removeClass("active");
    $('#historicalDataButton').addClass("active");
}

function onAddNewLayout() {

}

function getCurrentLayouts() {
    return [];
}

function generateOptions(layouts) {
    let options = "";
    layouts.forEach(layout => {
        options += `<option value="${layout.uuid}">${layout.name}(${layout.creationTime})</option>`;
    });
    $('#layoutSelect').html(options);
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