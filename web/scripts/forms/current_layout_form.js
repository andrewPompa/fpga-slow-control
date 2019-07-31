const dateType = {
    date: 'date',
    math: 'math',
    hex: 'hex'
};

class CurrentLayoutForm {
    constructor() {
        this.container = null;
        this.charts = [];
        this.formControls = null;
        this.layout = new Layout('chartsContainer');
        this.registerFormControls();
        this.chartForm = new ChartForm();
        this.chartForm.addListener(this);
    }

    start() {
        this.reset();
        this.chartForm.generate('newLayoutChartFormContainer');
    }

    stop() {
        this.reset();
        $('#newLayoutChartFormContainer').html('');
    }

    setName(name) {
        this.formControls.setValue('name', name);
        $('#layoutNameInput').val(name);

    }

    reset() {
        this.chartForm = new ChartForm();
        this.chartForm.addListener(this);
        this.registerFormControls();
        $('#layoutNameInput').val('');
        $('#chartsContainer').html('');
        this.layout.charts.forEach(chart => chart.removeInterval());
        this.layout = new Layout('chartsContainer');

    }

    registerFormControls() {
        this.formControls = new FormControls();
        this.formControls.add('name', '', (value) => value.match('^[\\w\\s]+$'), 'Please insert layout name', 'layoutNameInputError');
        this.formControls.addList(
            'controls',
            [],
            () => (layout.inputs && layout.inputs.length >= 1) || (layout.charts && layout.charts.length >= 1),
            'Please add some items to layout',
            'invalidLayoutError'
        );
    }

    onNewChart(chartData) {
        this.layout.addNewChart(chartData, true);
    }

    isActiveLayoutChanged() {
        const layout = this.layout;
        const layoutObject = {name: this.formControls.getValue('name'), controls: {inputs: layout.getInputs(), charts: layout.getCharts()}};
        if (!persistedLayout && layoutObject.name === '' && layoutObject.controls.inputs.length === 0 && layoutObject.controls.charts.length === 0) {
            return false;
        } else if (!persistedLayout) {
            return true;
        }
        const persistedLayoutObject = {name: persistedLayout.name, controls: {inputs: persistedLayout.getInputs(), charts: persistedLayout.getCharts()}};
        console.log(layoutObject);
        console.log(persistedLayoutObject);
        console.log(JSON.stringify(layoutObject) !== JSON.stringify(persistedLayoutObject));
        return layout.uuid && JSON.stringify(layoutObject) !== JSON.stringify(persistedLayoutObject);
    }

    validateAndSaveLayout() {
        if (this.formControls.isValid()) {
            const layoutObject = {name: this.formControls.getValue('name'), controls: {inputs: this.layout.getInputs(), charts: this.layout.getCharts()}};
            if (this.layout.uuid) {
                configurationService.put(this.layout.uuid, layoutObject, () => {
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
}