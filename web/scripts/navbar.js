let configurationService = new ConfigurationService();
let wordService = new WordsService();
let newLayoutTextboxRadio;
let newLayoutChartRadio;
let persistedLayout = null;
let currentDataButton;
let historicalLayoutConfigurer = new HistoricalLayoutConfigurer();
let historicConfigurationService = new HistoricConfigurationService();
let isCurrentLayout = true;
let currentLayoutForm = new CurrentLayoutForm();

$(document).ready(() => {
    currentDataButton = $('#currentDataButton');
    currentDataButton.click();
    resetCurrentLayout();
});

function resetCurrentLayout() {
    currentLayoutForm.reset();
    clearNewLayoutTextboxForm();
}

function onClickCurrentDataButton() {
    $('#historicalDataButton').removeClass("active");
    $('#activeLayoutViewContainer').removeAttr('hidden');
    $('#currentDataContainer').removeAttr('hidden');
    currentDataButton.addClass("active");
    layoutInfoListAll();
    currentLayoutForm.start();
    historicalLayoutConfigurer.stop();
    isCurrentLayout = true;
}

function onClickHistoricalDataButton() {
    if (currentLayoutForm.isActiveLayoutChanged()) {
        if (!confirm('Edited layout is changed, would you like to update it?')) {
            return;
        }
        currentLayoutForm.validateAndSaveLayout();
    }
    resetCurrentLayout();
    currentDataButton.removeClass("active");
    $('#historicalDataButton').addClass("active");
    $('#activeLayoutViewContainer').attr('hidden', '');
    $('#currentDataContainer').attr('hidden', '');
    historicalLayoutConfigurer.start();

    $('#newLayoutChartFormContainer').html('');

    isCurrentLayout = false;

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
        persistedLayout = new Layout('chartsContainer');
        persistedLayout.uuid = uuid;
        persistedLayout.name = configuration.name;

        currentLayoutForm.layout.uuid = uuid;
        currentLayoutForm.layout.name = configuration.name;
        currentLayoutForm.setName(configuration.name);
        configuration.controls.inputs.forEach(input => currentLayoutForm.layout.addNewInput(input));
        configuration.controls.charts.forEach(chart => currentLayoutForm.layout.addNewChart(chart, true));

        persistedLayout.inputs = [...currentLayoutForm.layout.inputs];
        persistedLayout.charts = [...currentLayoutForm.layout.charts];
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

function onAddNewLayout() {
    if (isCurrentLayout === true) {
        if (currentLayoutForm.isActiveLayoutChanged()) {
            if (!confirm('Edited layout is changed, would you like to update it?')) {
                return;
            }
            currentLayoutForm.validateAndSaveLayout();
        }
        resetCurrentLayout();
    } else {
        historicalLayoutConfigurer.addNewLayout();
    }

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