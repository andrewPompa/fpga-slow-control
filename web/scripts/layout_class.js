class Layout {
    constructor(containerForInputsName) {
        this.inputCounter = 0;
        this.containerForInputsName = containerForInputsName;
        this.inputs = [];
        this.charts = [];
        this.name = '';
    }

    getWords(inputId) {
        const input = this.inputs.find(i => i.id === inputId);
        if (!input) {
            return;
        }
        wordService.get(input.item.address, input.item.words, (result) => {
            console.log(result);
            const nums = byteArrayToNumList(base64ToByteArray(result));
            console.log(nums);
            let hex = '0x';
            nums.forEach(num => hex += num.toString(16).toUpperCase());
            console.log(hex);
            input.item.setValue(hex + "([" + nums.join(',') + "])");
        });
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
        if (!confirm('Are you sure you want to save this thing into the database?')) {
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