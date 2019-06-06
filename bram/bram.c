#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>
#include "bram.h"
#include "base64.h"
#include "arguments_validator.h"
#include "properties_parser/properties_parser.h"

int main(int argc, char *argv[]) {
    char *validation_result = validate_arguments(argc, argv);
    if (validation_result != NULL) {
        exit(EXIT_FAILURE);
    }
    program_mode program_mode_value = {NOT_FOUND, 0, NULL, 0};
    get_program_mode(argc, argv, &program_mode_value);

    if (program_mode_value.mode == NOT_FOUND) {
        exit(EXIT_FAILURE);
    }
    if (program_mode_value.mode == READ) {
        read_from_bram(program_mode_value.address, program_mode_value.words);
    } else if (program_mode_value.mode == WRITE) {
        write_to_bram(program_mode_value.address, program_mode_value.value, program_mode_value.words);
    }
}

void read_from_bram(long start_address, long words) {
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd == -1) {
        exit(EXIT_FAILURE);
    }
    size_t bram_size = words << 2;
    size_t pagesize = sysconf(_SC_PAGE_SIZE);
    off_t page_base = (start_address / pagesize) * pagesize;
    off_t page_offset = start_address - page_base;
    unsigned char *bram = mmap(NULL, page_offset + bram_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, page_base);
    if (bram == MAP_FAILED) {
        exit(EXIT_FAILURE);
    }
    unsigned char *word_bytes = malloc(bram_size);
    for (int i = 0; i < bram_size; ++i) {
        word_bytes[i] = bram[i];
    }
    size_t encode_size = get_encoded_length(bram_size);
    char *encoded = malloc(encode_size);
    int result = base64_encode(word_bytes, bram_size, encoded, encode_size);
    if (result != 0) {
        free(bram);
        free(encoded);
        free(word_bytes);
        exit(EXIT_FAILURE);
    }
    printf("%s", encoded);
    close(fd);
    munmap(bram, bram_size);
    free(encoded);
    free(word_bytes);
}

void write_to_bram(long start_address, char *bytes, long words) {
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd == -1) {
        printf("ERROR during opening dev mem\n");
        exit(EXIT_FAILURE);
    }
    size_t bram_size = words << 2;
    size_t pagesize = sysconf(_SC_PAGE_SIZE);
    off_t page_base = (start_address / pagesize) * pagesize;
    off_t page_offset = start_address - page_base;
    unsigned char *bram = mmap(NULL, page_offset + bram_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, page_base);
    if (bram == MAP_FAILED) {
        printf("ERROR during opening mmap\n");
        exit(EXIT_FAILURE);
    }
    size_t decoded_length = get_decoded_length(strlen(bytes));
    unsigned char *decoded = malloc(decoded_length);
    int result = base64_decode(bytes, strlen(bytes), decoded, bram_size);
    if (result != 0) {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < bram_size; ++i) {
        bram[page_offset + i] = decoded[i];
    }
    close(fd);
    munmap(bram, bram_size);
    free(decoded);
//    free(bytes);
}
