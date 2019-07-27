class FormControls {
    constructor() {
        this.controls = [];
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

    checkValidity(control) {
        const errorControl = $(`#${control.errorDiv}`);
        if (!control.validationFunction(control.value)) {
            errorControl.css("display", "block");
            errorControl.html(control.errorMessage);
        } else {
            errorControl.css("display", "none");
            errorControl.html('');
        }
    }

    isValid() {
        return this.controls.every(control => this.checkValidity(control) === true);
    }

    validateAll() {
        this.controls.forEach(formControl => this.checkValidity(formControl));
    }
}