class Toast {
    constructor(type, message) {
        this.type = type;
        this.message = message;
        toastr.options.positionClass = 'toast-top-full-width';
        toastr.options.extendedTimeOut = 0; //1000;
        toastr.options.timeOut = 1000;
        toastr.options.fadeOut = 250;
        toastr.options.fadeIn = 250;
        // toastr.options.positionClass = 'toast-top';
    }

    show() {
        toastr[this.type](this.message);
    }
}