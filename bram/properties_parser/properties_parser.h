#ifndef FPGA_SLOW_CONTROL_PROPERTIES_PARSER_H
#define FPGA_SLOW_CONTROL_PROPERTIES_PARSER_H

#endif //FPGA_SLOW_CONTROL_PROPERTIES_PARSER_H

static const long ERROR_VALUE = -1;
static const char *ADDRESS_OFFSET_KEY = "ADDRESS_OFFSET";
static const char *ADDRESS_HIGHEST_KEY = "ADDRESS_HIGHEST";

long get_address_offset(FILE *conf_file_location);

long get_highest_address(FILE *conf_file_location);

char *find_matching_line(FILE *file, const char *string_to_find);

char *find_value(char *line, const char *key);