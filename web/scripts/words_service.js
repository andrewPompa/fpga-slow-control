class WordsService {
    constructor() {
    }

    get(address, numOfWords, onSuccess) {
        address = parseInt(address);
        numOfWords = parseInt(numOfWords);
        const ajax = {};
        ajax.type = "GET";
        ajax.url = `/address/${address}?words=${numOfWords}`;
        ajax.dataType = "text";
        ajax.success = onSuccess;
        ajax.error = function (response, request, jqXHR) {
            console.log(response);
            console.log(request);
            console.log(jqXHR);
        };
        $.ajax(ajax);
    }

    send(address, numOfWords, hexValue, onSuccess) {
        address = parseInt(address);
        numOfWords = parseInt(numOfWords);
        const ajax = {};
        ajax.type = "PATCH";
        ajax.url = `/address/${address}?words=${numOfWords}`;
        ajax.contentType = "application/octet-stream";
        ajax.data = hexToByteArray(hexValue, numOfWords);
        ajax.success = onSuccess;
        ajax.processData = false;
        $.ajax(ajax);
    }
}