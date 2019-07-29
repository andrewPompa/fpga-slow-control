class Layout {
    constructor(containerForInputsName) {
        this.inputCounter = 0;
        this.chartCounter = 0;
        this.containerForInputsName = containerForInputsName;
        this.inputs = [];
        this.charts = [];
        this.name = '';
    }

    getWords(inputId) {
        let input = this.inputs.find(i => i.id === inputId);
        if (!input) {
            return;
        }
        input = input.item;
        if (input.type === dateType.hex) {
            wordService.getHex(input.address, input.words, (hex, nums) => input.setValue(hex + "([" + nums.join(',') + "])"));
        } else if (input.type === dateType.date) {
            wordService.getInt(input.address, (seconds) => input.setValue(secondsToHourMinutesSeconds(seconds)));
        } else if (input.type === dateType.math) {
            wordService.getMath(input.address, input.formula, (result) => input.setValue(result));
        }
    }

    validateAndSendInput(inputId) {
        const input = this.inputs.find(i => i.id === inputId);
        if (!input) {
            return;
        }
        console.log(input);
        if (input.item.validate()) {
            wordService.send(input.item.address, input.item.words, input.item.value, (response) => console.log(response));
        }
    }

    addNewChart(chartData) {
        console.log(chartData);
        const id = this.chartCounter++;
        const chartItem = new ChartItem(id, chartData.name, chartData.interval, chartData.series);
        this.charts.push(chartItem);
        const canvas = chartItem.buildCanvas();
        $('#chartsContainer').append(canvas);
        chartItem.buildChart();
    }

    addNewInput(input) {
        const inputItem = new InputItem();
        inputItem.id = this.inputCounter++;
        inputItem.name = input.name;
        inputItem.address = input.address;
        inputItem.words = input.words;
        inputItem.type = input.dataType;
        inputItem.readOnly = input.readOnly;
        inputItem.formula = input.formula;
        this.inputs.push({id: inputItem.id, item: inputItem});
        $('#' + this.containerForInputsName).append(inputItem.generate());
    }

    removeInput(id) {
        if (!confirm('Are you sure to remove that input?')) {
            return;
        }
        const inputIndex = this.inputs.findIndex(i => i.id === id);
        if (inputIndex === -1) {
            console.log(this.inputs);
            return;
        }
        $("#input_" + inputIndex).remove();
        this.inputs.splice(inputIndex, 1);
    }
}