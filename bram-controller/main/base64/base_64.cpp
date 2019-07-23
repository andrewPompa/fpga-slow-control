//
// Created by andrzej on 25.06.19.
//

#include <memory>
#include "base_64.hpp"
//#include <iostream>

static const std::string base64Chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

static inline bool isBase64(u_char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string Base64::encode(u_char *buffer, uint bufferLength) {
    std::string ret;
    int i = 0;
    int j = 0;
    u_char chars3[3];
    u_char chars4[4];

    while (bufferLength--) {
        chars3[i++] = *(buffer++);
        if (i == 3) {
            chars4[0] = (chars3[0] & 0xfc) >> 2;
            chars4[1] = ((chars3[0] & 0x03) << 4) + ((chars3[1] & 0xf0) >> 4);
            chars4[2] = ((chars3[1] & 0x0f) << 2) + ((chars3[2] & 0xc0) >> 6);
            chars4[3] = chars3[2] & 0x3f;

            for (i = 0; (i < 4); i++)
                ret += base64Chars[chars4[i]];
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 3; j++) {
            chars3[j] = '\0';
        }

        chars4[0] = (chars3[0] & 0xfc) >> 2;
        chars4[1] = ((chars3[0] & 0x03) << 4) + ((chars3[1] & 0xf0) >> 4);
        chars4[2] = ((chars3[1] & 0x0f) << 2) + ((chars3[2] & 0xc0) >> 6);
        chars4[3] = chars3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++) {
            ret += base64Chars[chars4[j]];
        }
        while ((i++ < 3)) {
            ret += '=';
        }
    }
    return ret;
}

std::shared_ptr<uint> Base64::decodeWords(std::string const &encoded) {
    int inputLen = encoded.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    u_char chars3[3];
    u_char chars4[4];
    std::vector<u_char> decodedChars;

    while (inputLen-- && (encoded[in_] != '=') && isBase64(encoded[in_])) {
        chars4[i++] = encoded[in_];
        in_++;
        if (i == 4) {
            for (i = 0; i < 4; i++) {
                chars4[i] = base64Chars.find(chars4[i]);
            }

            chars3[0] = (chars4[0] << 2) + ((chars4[1] & 0x30) >> 4);
            chars3[1] = ((chars4[1] & 0xf) << 4) + ((chars4[2] & 0x3c) >> 2);
            chars3[2] = ((chars4[2] & 0x3) << 6) + chars4[3];

            for (i = 0; (i < 3); i++) {
                decodedChars.push_back(chars3[i]);
            }
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 4; j++) {
            chars4[j] = 0;
        }
        for (j = 0; j < 4; j++) {
            chars4[j] = base64Chars.find(chars4[j]);
        }
        chars3[0] = (chars4[0] << 2) + ((chars4[1] & 0x30) >> 4);
        chars3[1] = ((chars4[1] & 0xf) << 4) + ((chars4[2] & 0x3c) >> 2);
        chars3[2] = ((chars4[2] & 0x3) << 6) + chars4[3];

        for (j = 0; (j < i - 1); j++) {
            decodedChars.push_back(chars3[j]);
        }
    }
    std::shared_ptr<uint> bytes(new uint[(decodedChars.size() +  decodedChars.size() % 4) / 4]);
    uint w = 0;
    for (int k = 0; k < decodedChars.size(); ++k) {
        w |= decodedChars[k] << (8 * (k - k / 4 * 4));
        if ((k + 1) % 4 == 0 || k == decodedChars.size() - 1) {
            bytes.get()[k / 4] = w;
            w = 0;
        }
    }
    return bytes;
}
