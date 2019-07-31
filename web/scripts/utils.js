function base64ToByteArray(base64) {
    const raw = window.atob(base64);
    const rawLength = raw.length;
    const array = new Uint8Array(new ArrayBuffer(rawLength));

    for (let i = 0; i < rawLength; i++) {
        array[i] = raw.charCodeAt(i);
    }
    return array;
}

function byteArrayToNumList(array) {
    let numbers = [];
    let w = 0;
    for (let k = 0; k < array.length; ++k) {
        w |= array[k] << (8 * (k - Math.floor(k / 4) * 4));
        if ((k + 1) % 4 === 0 || k === array.length - 1) {
            numbers[Math.floor(k / 4)] = w;
            w = 0;
        }
    }
    return numbers;
}

function base64ToMathValue(value, formula) {
    const nums = byteArrayToNumList(base64ToByteArray(value));
    if (!nums || !nums.length || nums.length === 0) {
        return NaN;
    }
    console.log(nums[0]);
    console.log(formula);
    const mathEquation = math.parse(formula).compile();
    let scope = {x: nums[0]};
    return  mathEquation.evaluate(scope);
}


function hexToByteArray(hex, numOfWords) {
    const wordBytes = new Uint8Array(numOfWords * 4);
    const hexWords = [];
    hex = hex.substring(2, hex.length);
    while (hex.length > 8) {
        hexWords.push(hex.substr(0, 8));
        hex = hex.substring(8, hex.length);
    }
    hexWords.push(hex);
    for (let i = 0; i < hexWords.length; ++i) {
        const parsedWord = parseInt(hexWords[i], 16);
        wordBytes[i * 4 + 3] = (parsedWord >> 24) & 0xFF;
        wordBytes[i * 4 + 2] = (parsedWord >> 16) & 0xFF;
        wordBytes[i * 4 + 1] = (parsedWord >> 8) & 0xFF;
        wordBytes[i * 4] = parsedWord & 0xFF;
    }
    return wordBytes;
}

function secondsToHourMinutesSeconds(seconds) {
    const h = Math.floor(seconds / 3600);
    const m = Math.floor(seconds % 3600 / 60);
    const s = Math.floor(seconds % 3600 % 60);

    const hDisplay = h > 9 ? h : "0" + h;
    const mDisplay = m > 9 ? m : "0" + m;
    const sDisplay = s > 9 ? s : "0" + s;

    return hDisplay + mDisplay + sDisplay;
}

function currentTimeInMillis() {
    const now = new Date();
    return now.getHours() + ":" + now.getMinutes() + ":" + now.getSeconds() + "." + now.getMilliseconds();
}

function guid() {
    function s4() {
        return Math.floor((1 + Math.random()) * 0x10000)
            .toString(16)
            .substring(1);
    }

    return s4() + s4() + s4() + s4() + s4() + s4() + s4() + s4();
}