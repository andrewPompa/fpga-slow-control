#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "properties_parser.h"

long get_address_offset(FILE *conf_file_location) {
    if (conf_file_location == NULL) {
        return ERROR_VALUE;
    }
    char *matching_line = find_matching_line(conf_file_location, ADDRESS_OFFSET_KEY);
    if (matching_line == NULL) {
        return ERROR_VALUE;
    }
    matching_line = find_value(matching_line, ADDRESS_OFFSET_KEY);
    if (matching_line == NULL) {
        return ERROR_VALUE;
    }
    return strtol(matching_line, NULL, 0);
}

long get_highest_address(FILE *conf_file_location) {
    if (conf_file_location == NULL) {
        return ERROR_VALUE;
    }
    char *matching_line = find_matching_line(conf_file_location, ADDRESS_HIGHEST_KEY);
    if (matching_line == NULL) {
        return ERROR_VALUE;
    }
    matching_line = find_value(matching_line, ADDRESS_HIGHEST_KEY);
    if (matching_line == NULL) {
        return ERROR_VALUE;
    }
    return strtol(matching_line, NULL, 0);
}


char *find_matching_line(FILE *file, const char *string_to_find) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read = getline(&line, &len, file);
    char *key = NULL;
    while (read != -1) {
        key = strstr(line, string_to_find);
        if (key != NULL) {
            break;
        }
        read = getline(&line, &len, file);
    }
    fclose(file);
    return key;
}

char *find_value(char *line, const char *key) {
    line += strlen(key);

    bool found_equals_char = false;
    char current_char = line[0];
    while (current_char != '\0') {
        if (current_char == '=') {
            found_equals_char = true;
        } else if (current_char != ' ' && found_equals_char == true) {
            return line;
        }
        ++line;
        current_char = line[0];
    }
    return NULL;
}