//
// Created by andrzej on 06.06.19.
//

#ifndef BRAM_BASE64_H
#define BRAM_BASE64_H

#endif //BRAM_BASE64_H

size_t get_encoded_length(long bytes);

size_t get_decoded_length(long encoded_bytes);

int base64_encode(const void *data_buf, size_t data_length, char *result, size_t result_size);

int base64_decode(char *in, size_t inLen, unsigned char *out, size_t outLen);
