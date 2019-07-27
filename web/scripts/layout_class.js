class Layout {
    constructor(containerForInputsName) {
        this.inputCounter = 0;
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
        wordService.get(input.address, input.words, (result) => {
            const nums = byteArrayToNumList(base64ToByteArray(result));
            if (input.type === dateType.hex) {
                let hex = '0x';
                nums.forEach(num => hex += num.toString(16).toUpperCase());
                input.setValue(hex + "([" + nums.join(',') + "])");
            } else if (input.type === dateType.date) {
                const nums = byteArrayToNumList(base64ToByteArray(result));
                if (nums.length !== 1) {
                    console.log('date has to be 1 word!');
                    return;
                }
                const dateInSeconds = nums[0];
                console.log(dateInSeconds);
                const h = Math.floor(dateInSeconds / 3600);
                const m = Math.floor(dateInSeconds % 3600 / 60);
                const s = Math.floor(dateInSeconds % 3600 % 60);
                console.log(h);
                console.log(m);
                console.log(s);

                const hDisplay = h > 0 ? h + (h === 1 ? " hour, " : " hours, ") : "";
                const mDisplay = m > 0 ? m + (m === 1 ? " minute, " : " minutes, ") : "";
                const sDisplay = s > 0 ? s + (s === 1 ? " second" : " seconds") : "";
                input.setValue(hDisplay + mDisplay + sDisplay);
            } else if (input.type === dateType.math) {
                const nums = byteArrayToNumList(base64ToByteArray(result));
                if (nums.length !== 1) {
                    console.log('date has to be 1 word!');
                    return;
                }
                const dateInSeconds = nums[0];
                console.log(dateInSeconds);
                const mathEquation = math.parse(input.formula).compile();
                let scope = {x: dateInSeconds};
                input.setValue(mathEquation.evaluate(scope));
            }

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