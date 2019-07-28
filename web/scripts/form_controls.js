class FormControls {
    constructor() {
        this.controls = [];
    }

    getValues() {
        const result = {};
        this.controls.forEach(control => result[control.name] = control.value);
        return result;
    }

    get (controlName) {
        return this.controls.find(formControl => formControl.name === controlName);
    };

    getValue(controlName) {
        const control = this.controls.find(formControl => formControl.name === controlName);
        return control ? control.value : null;
    }

    add(name, value, validationFunction, errorMessage, errorDiv) {
        this.controls.push({
            name: name, value: value, validationFunction: validationFunction, errorMessage: errorMessage, errorDiv: errorDiv, getParentForm: () => (this)
        });
    }

    setValue(controlName, value) {
        const c = this.get(controlName);
        if (c) {
            c.value = value;
            this.checkValidity(c);
        }
    }

    setValueNoValidate(controlName, value) {
        const c = this.get(controlName);
        if (c) {
            c.value = value;
        }
    }

    checkValidity(control) {
        let isValid = true;
        const errorControl = $(`#${control.errorDiv}`);
        if (!control.validationFunction(control.value)) {
            isValid = false;
            errorControl.css("display", "block");
            errorControl.html(control.errorMessage);
        } else {
            errorControl.css("display", "none");
            errorControl.html('');
        }
        return isValid;
    }

    isValid() {
        let isValid = true;
        this.controls.forEach(control => isValid = this.checkValidity(control) === false ? false : isValid);
        return isValid;
    }

    validateAll() {
        this.controls.forEach(formControl => this.checkValidity(formControl));
    }
}