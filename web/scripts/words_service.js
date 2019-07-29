class WordsService {
    constructor() {
    }

    getHex(address, numOfWords, onSuccess) {
        this.get(address, numOfWords, (result) => {
            const nums = byteArrayToNumList(base64ToByteArray(result));
            if (!nums || !nums.length || nums.length === 0) {
                onSuccess(null, []);
                return;
            }
            let hex = '0x';
            nums.forEach(num => hex += num.toString(16).toUpperCase());
            onSuccess(hex, nums);
        });
    }

    getInt(address, onSuccess) {
        this.get(address, 1, (result) => {
            const nums = byteArrayToNumList(base64ToByteArray(result));
            if (!nums || !nums.length || nums.length === 0) {
                onSuccess(null);
                return;
            }
            onSuccess(nums[0]);
        });
    }

    getMath(address, formula, onSuccess) {
        this.get(address, 1, (result) => {
            const nums = byteArrayToNumList(base64ToByteArray(result));
            if (!nums || !nums.length || nums.length === 0) {
                onSuccess(null);
                return;
            }
            const mathEquation = math.parse(formula).compile();
            let scope = {x: nums[0]};
            onSuccess(mathEquation.evaluate(scope));
        })
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