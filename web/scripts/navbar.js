let selectLayout;
let currentDataButton;
let currentLayouts = [];

$(document).ready(() => {
    selectLayout = $('#selectForm');
    currentDataButton = $('#currentDataButton');
    currentDataButton.click();
});


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
    $('#selectForm').attr('hidden', 'hidden');
}

function onChangeLayoutSelect(selectedIndex) {
    console.log(selectedIndex);
    console.log(selectedIndex[0]);
    console.log(selectedIndex.length);
    // for (let i = 0; i <)
    //     selectedIndex.forEach(option => console.log(option));
    // if (selectedIndex === 0) {
    //     return;
    // }

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