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
        printf("Cannot open conf file!\n");
        exit(EXIT_FAILURE);
    }
    long bram_address_offset = get_address_offset(file);
    file = fopen(conf_file_location, "r");
    long bram_highest_address = get_highest_address(file);

    if (program_mode_value.mode == NOT_FOUND) {
        printf("Program mode not specified properly!\n");
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    if (program_mode_value.mode == READ) {
        read_from_bram(bram_address_offset, bram_highest_address, program_mode_value.offset, program_mode_value.size);
    } else if (program_mode_value.mode == WRITE) {
        printf("writing ");
        print_bytes_as_hex(program_mode_value.value, program_mode_value.value_size);
        printf(", to address: 0x%lX\n", bram_address_offset);

        write_to_bram(bram_address_offset, bram_highest_address, program_mode_value.value, program_mode_value.value_size, program_mode_value.offset);
    } else if (program_mode_value.mode == CLEAR) {
//        write_to_bram(bram_address_offset, bram_highest_address, 0x0, 0);
    }
}
//0xFF00FF00FF00FF00FF00FF00FF00FF00FF00FF00
void read_from_bram(long start_address, long max_address, long offset_bytes, long word_size) {
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd == -1) {
        printf("ERROR: cannot open BRAM block...\n");
        exit(EXIT_FAILURE);
    }
//    int bram_size = max_address - start_address;
//    printf("num of bits in block: %d\n", bram_size);
//    char * bram = (char *) mmap(NULL, bram_size, PROT_READ, MAP_SHARED, fd, start_address + offset);
//    char *word_bytes = malloc(word_size);
//    for (int i = 0; i < word_size; ++i) {
//        printf("[%d] = 0x%X\n", i, bram[i]);
//        word_bytes[i] = bram[i];
//    }
//    print_bytes_as_hex(word_bytes, word_size);
    close(fd);
}

void write_to_bram(long start_address, long max_address, char *bytes, long bytes_size, long offset) {
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    char *bram;
    if (fd == -1) {
        printf("ERROR: cannot open BRAM block...\n");
        exit(EXIT_FAILURE);
    }

    signed int bram_size = max_address - start_address;
    printf("num of bytes in block: %d, bytes size: %ld\n", (bram_size >> 3), bytes_size);
    bram = (char *) mmap(NULL, bram_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, start_address + offset);
    if (bram == MAP_FAILED) {
        printf("ERROR: cannot open BRAM block...\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < bytes_size; ++i) {
        printf("%X\n", bytes[i]);
        bram[i] = bytes[i];
    }
    close(fd);
}
