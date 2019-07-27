class Layout {
    constructor(containerForInputsName) {
        this.inputCounter = 0;
        this.containerForInputsName = containerForInputsName;
        this.inputs = [];
        this.charts = [];
        this.name = '';
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
        console.log(this.inputs.length);
        this.inputs.push({id: inputItem.id, item: inputItem});
        $('#' + this.containerForInputsName).append(inputItem.generate());
    }

    removeInput(id) {
        const inputIndex = this.inputs.findIndex(i => i.id === id);
        if (inputIndex === -1) {
            console.log(this.inputs);
            return;
        }
        $("#input_" + inputIndex).remove();
        this.inputs.splice(inputIndex, 1);
        console.log(this.inputs);
    }
}