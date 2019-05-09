#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>
#include "bram.h"
#include "arguments_validator.h"
#include "properties_parser/properties_parser.h"


void print_bytes_as_hex(char *bytes, int size) {
    printf("value: 0x");
    for (int i = 0; i < size; ++i) {
        printf("%X", bytes[i]);
    }
}

int main(int argc, char *argv[]) {

    char *validation_result = validate_arguments(argc, argv);
    if (validation_result != NULL) {
        printf("%s\n", validation_result);
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }
    char *conf_file_location = get_conf_file_location(argv);
    program_mode program_mode_value = {NOT_FOUND, 0, 0, NULL, 0};
    get_program_mode(argc, argv, &program_mode_value);

    FILE *file;
    file = fopen(conf_file_location, "r");
    if (file == NULL) {
        printf("ERROR: cannot open conf file!\n");
        exit(EXIT_FAILURE);
    }
    long bram_address_offset = get_address_offset(file);
    file = fopen(conf_file_location, "r");
    long bram_highest_address = get_highest_address(file);

    if (program_mode_value.mode == NOT_FOUND) {
        printf("ERROR: program mode not specified properly!\n");
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }
    if (bram_highest_address - bram_address_offset <= 0) {
        printf("ERROR: highest offset is smaller than address offset!\n");
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    if (program_mode_value.mode == READ) {
        read_from_bram(bram_address_offset, bram_highest_address, program_mode_value.offset, program_mode_value.size);
    } else if (program_mode_value.mode == WRITE) {
        write_to_bram(bram_address_offset, bram_highest_address, program_mode_value.value, program_mode_value.value_size, program_mode_value.offset);
    } else if (program_mode_value.mode == CLEAR) {
        clear_bram(bram_address_offset, bram_highest_address);
    }
}
void read_from_bram(long start_address, long max_address, long offset_bytes, long word_size) {
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd == -1) {
        printf("ERROR: cannot open BRAM block...\n");
        exit(EXIT_FAILURE);
    }
    int bram_size = max_address - start_address + 1;
    printf("num of bits in block: %d\n", bram_size);
    char * bram = (char *) mmap(NULL, bram_size, PROT_READ, MAP_SHARED, fd, start_address);
    if (bram == MAP_FAILED) {
        printf("ERROR: cannot open BRAM block...\n");
        exit(EXIT_FAILURE);
    }
    if (start_address + (offset_bytes << 3) + (word_size << 3) > max_address) {
        printf("ERROR: offset with word size exceeds address space\n");
        exit(EXIT_FAILURE);
    }
    if (word_size == 0) {
        word_size = (bram_size >> 3) + offset_bytes;
    }
    bram += offset_bytes;

    char *word_bytes = malloc(word_size);
    for (int i = 0; i < word_size; ++i) {
        printf("[0x%lX] = 0x%X\n", start_address + (offset_bytes << 3) + (i << 3), bram[0]);
        word_bytes[i] = bram[0];
        bram++;
    }
    print_bytes_as_hex(word_bytes, word_size);
    printf("\n");
    close(fd);
}

void write_to_bram(long start_address, long max_address, char *bytes, long bytes_size, long offset) {
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    char *bram;
    if (fd == -1) {
        printf("ERROR: cannot open BRAM block...\n");
        exit(EXIT_FAILURE);
    }
    if (start_address + (bytes_size << 3) + (offset << 3) > max_address + 1) {
        printf("ERROR: offset with value size exceeds address space\n");
        exit(EXIT_FAILURE);
    }
    signed int bram_size = max_address - start_address + 1;
    printf("num of bytes in block: %d, bytes size: %ld\n", (bram_size >> 3), bytes_size);
    bram = (char *) mmap(NULL, bram_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, start_address );
    bram += offset;
    if (bram == MAP_FAILED) {
        printf("ERROR: cannot open BRAM block...\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < bytes_size; ++i) {
        bram[i] = bytes[i];
    }
    close(fd);
    printf("value written into memory\n");
}

void clear_bram(long start_address, long max_address) {
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    char *bram;
    if (fd == -1) {
        printf("ERROR: cannot open BRAM block...\n");
        exit(EXIT_FAILURE);
    }

    signed int bram_size = max_address - start_address;
    bram = (char *) mmap(NULL, bram_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, start_address );
    for (int i = 0; i < bram_size >> 3; ++i) {
        bram[i] = 0;
    }
    printf("memory cleared\n");
}
