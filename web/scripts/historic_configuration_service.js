class HistoricConfigurationService {
    constructor() {
    }

    getList(onSuccess) {
        const ajax = {};
        ajax.type = "GET";
        ajax.url = `/historic-configuration/all`;
        ajax.contentType = "application/json";
        ajax.dataType = "json";
        ajax.success = onSuccess;
        $.ajax(ajax);
    }

    getData(uuid, chartId, onSuccess) {
        const ajax = {};
        ajax.type = "GET";
        ajax.url = `/historic-data/${uuid}/${chartId}`;
        ajax.contentType = "application/json";
        ajax.dataType = "json";
        ajax.success = onSuccess;
        $.ajax(ajax);
    }

    makeInactive(uuid, onSuccess) {
        const ajax = {};
        ajax.type = "POST";
        ajax.url = `/historic-configuration/${uuid}/inactive`;
        ajax.success = onSuccess;
        $.ajax(ajax);
    }

    put(uuid, configuration, onSuccess) {
        const ajax = {};
        ajax.type = "PUT";
        ajax.url = `/historic-configuration/${uuid}`;
        ajax.contentType = "application/json";
        ajax.dataType = "json";
        ajax.data = JSON.stringify(configuration);
        ajax.success = onSuccess;
        $.ajax(ajax);
    }

    get(uuid, onSuccess) {
        const ajax = {};
        ajax.type = "GET";
        ajax.url = `/historic-configuration/${uuid}`;
        ajax.contentType = "application/json";
        ajax.dataType = "json";
        ajax.success = onSuccess;
        $.ajax(ajax);
    }

    post(configuration, onSuccess) {
        const ajax = {};
        ajax.type = "POST";
        ajax.url = `/historic-configuration`;
        ajax.contentType = "application/json";
        ajax.dataType = "json";
        ajax.data = JSON.stringify(configuration);
        ajax.success = onSuccess;
        $.ajax(ajax);
    }

    remove(uuid, onSuccess) {
        const ajax = {};
        ajax.type = "DELETE";
        ajax.url = `/historic-configuration/${uuid}`;
        ajax.dataType  =  'html';
        ajax.success = onSuccess;
        $.ajax(ajax);
    }
}
