class ConfigurationService {
    constructor() {
    }

    getList(onSuccess) {
        const ajax = {};
        ajax.type = "GET";
        ajax.url = `/configuration/all`;
        ajax.contentType = "application/json";
        ajax.dataType = "json";
        ajax.success = onSuccess;
        $.ajax(ajax);
    }

    get(uuid, onSuccess) {
        const ajax = {};
        ajax.type = "GET";
        ajax.url = `/configuration/${uuid}`;
        ajax.contentType = "application/json";
        ajax.dataType = "json";
        ajax.success = onSuccess;
        $.ajax(ajax);
    }

    post(configuration, onSuccess) {
        const ajax = {};
        ajax.type = "POST";
        ajax.url = `/configuration`;
        ajax.contentType = "application/json";
        ajax.dataType = "json";
        ajax.data = JSON.stringify(configuration);
        ajax.success = onSuccess;
        $.ajax(ajax);
    }

    remove(uuid, onSuccess) {
        const ajax = {};
        ajax.type = "DELETE";
        ajax.url = `/configuration/${uuid}`;
        ajax.dataType  =  'html';
        ajax.success = onSuccess;
        $.ajax(ajax);
    }
}
