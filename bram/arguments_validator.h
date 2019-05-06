#ifndef BRAM_ARGUMENTS_VALIDATOR_H
#define BRAM_ARGUMENTS_VALIDATOR_H

#endif //BRAM_ARGUMENTS_VALIDATOR_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char *DEFAULT_CONF_LOCATION = "bram.conf";

enum MODE {
    READ, WRITE, CLEAR
};

typedef struct {
    enum MODE mode;
    long offset;
    long size;
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
        if (is_mode_argument(argv[1]) == true) {
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

void get_program_mode(int argc, char *argv[], program_mode *program_mode_value) {
    bool is_mode_selected = false;
    bool is_offset_selected = false;
    for (int i = 1; i < argc; ++i) {
        if (is_mode_argument(argv[1]) == true) {
            if (strcmp(argv[i], "-r") == 0) {
                program_mode_value->mode = READ;
            } else if (strcmp(argv[i], "-w") == 0) {
                program_mode_value->mode = WRITE;
            } else if (strcmp(argv[i], "-c") == 0) {
                program_mode_value->mode = CLEAR;
                return;
            }
            is_mode_selected = true;
        } else if (is_mode_selected == true && is_offset_selected == false) {
            program_mode_value->offset = strtol(argv[i], NULL, 0);
            is_offset_selected = true;
        } else if (is_mode_selected == true) {
            program_mode_value->size = strtol(argv[i], NULL, 0);
        }
    }
}