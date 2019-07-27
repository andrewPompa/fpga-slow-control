function base64ToByteArray(base64) {
    const raw = window.atob(base64);
    const rawLength = raw.length;
    const array = new Uint8Array(new ArrayBuffer(rawLength));

    for(let i = 0; i < rawLength; i++) {
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
        wordBytes[i * 4] = (parsedWord >> 24) & 0xFF;
        wordBytes[i * 4 + 1] = (parsedWord >> 16) & 0xFF;
        wordBytes[i * 4 + 2] = (parsedWord >> 8) & 0xFF;
        wordBytes[i * 4 + 3] = parsedWord & 0xFF;
    }
    return wordBytes;
}