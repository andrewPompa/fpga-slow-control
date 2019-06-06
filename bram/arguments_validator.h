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
    unsigned long address;
    char *value;
    int words;
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
    if (is_mode_selected == false) {
        return "mode not set!";
    }
    return NULL;
}

void get_program_mode(int argc, char *argv[], program_mode *program_mode_value) {
    if (is_mode_argument(argv[1]) == false) {
        return;
    }
    if (strcmp(argv[1], "-r") == 0) {
        program_mode_value->mode = READ;
    } else if (strcmp(argv[1], "-w") == 0) {
        program_mode_value->mode = WRITE;
    } else if (strcmp(argv[1], "-c") == 0) {
        program_mode_value->mode = CLEAR;
        return;
    }
    if (program_mode_value->mode == READ) {
        if (argc < 4) {
            exit(EXIT_FAILURE);
        }
        program_mode_value->address = strtol(argv[2], NULL, 0);
        program_mode_value->words = strtol(argv[3], NULL, 0);
    }
    if (program_mode_value->mode == WRITE) {
        if (argc < 5) {
            exit(EXIT_FAILURE);
        }
        program_mode_value->address = strtol(argv[2], NULL, 0);
        program_mode_value->words = strtol(argv[3], NULL, 0);
        program_mode_value->value = argv[4];
    }
}