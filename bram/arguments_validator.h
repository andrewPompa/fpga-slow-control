#ifndef BRAM_ARGUMENTS_VALIDATOR_H
#define BRAM_ARGUMENTS_VALIDATOR_H

#endif //BRAM_ARGUMENTS_VALIDATOR_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char *DEFAULT_CONF_LOCATION = "bram.conf";

enum MODE {
    READ, WRITE, CLEAR, NOT_FOUND
};

typedef struct {
    enum MODE mode;
    long offset;
    long size;
    char * value;
    int value_size;
} program_mode;

bool is_mode_argument(char *argument) {
    return (strcmp(argument, "-r") == 0 || strcmp(argument, "-w") == 0 || strcmp(argument, "-c") == 0);
}

char *validate_arguments(int argc, char *argv[]) {
    if (argc < 2) {
        return "Not enough arguments!";
    }

    bool is_mode_selected = false;
    for (int i = 1; i < argc; ++i) {
        if (is_mode_argument(argv[i]) == true) {
            if (is_mode_selected == true) {
                return "mode already set!";
            }
            is_mode_selected = true;
        }
    }
    return NULL;
}

char *get_conf_file_location(char *argv[]) {
    return is_mode_argument(argv[1]) == false ? argv[1] : DEFAULT_CONF_LOCATION;
}

char *map_hex_value_to_bytes(char* hex_value, int *size) {
    if (strlen(hex_value) <= 2) {
        return NULL;
    }
    hex_value += 2;
    char* byte_string = malloc(2);
    char* byte_value = malloc(strlen(hex_value) % 2 == 0 ? strlen(hex_value) / 2 : (strlen(hex_value) + 1) / 2);
    int j = 0;
    for (int i = 0; i < strlen(hex_value); i += 2) {
        if (i + 1 < strlen(hex_value)) {
            byte_string[0] = hex_value[i];
            byte_string[1] = hex_value[i + 1];
        } else {
            byte_string[0] = hex_value[i];
            byte_string[1] = '0';
        }
        char byte = strtol(byte_string, NULL, 16);
        byte_value[j++] = byte;
    }
    *size = j;
    return byte_value;
}

void get_program_mode(int argc, char *argv[], program_mode *program_mode_value) {
    int argument_offset = 1;
    if (is_mode_argument(argv[argument_offset]) == false) {
        argument_offset = 2;
    } else if (is_mode_argument(argv[argument_offset]) == false) {
        return;
    }
    if (strcmp(argv[argument_offset], "-r") == 0) {
        program_mode_value->mode = READ;
    } else if (strcmp(argv[argument_offset], "-w") == 0) {
        program_mode_value->mode = WRITE;
    } else if (strcmp(argv[argument_offset], "-c") == 0) {
        program_mode_value->mode = CLEAR;
        return;
    }
    if (program_mode_value->mode == READ) {
        if (argc > argument_offset + 1) {
            program_mode_value->offset = strtol(argv[argument_offset + 1], NULL, 0);
        }
        if (argc > argument_offset + 2) {
            program_mode_value->size = strtol(argv[argument_offset +  2], NULL, 0);
        }
    }
    if (program_mode_value->mode == WRITE) {
        if (argc > argument_offset + 1) {
            program_mode_value->value = map_hex_value_to_bytes(argv[argument_offset +  1], &program_mode_value->value_size);
        }
        if (argc > argument_offset + 2) {
            program_mode_value->offset = strtol(argv[argument_offset +  2], NULL, 0);
        }
    }
}