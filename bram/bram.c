#include <stdlib.h>
#include <stdio.h>
#include "bram.h"
#include "arguments_validator.h"
#include "properties_parser/properties_parser.h"


int main(int argc, char *argv[]) {

    char *validation_result = validate_arguments(argc, argv);
    if (validation_result != NULL) {
        printf("%s\n", validation_result);
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }
    char *conf_file_location = get_conf_file_location(argv);
    program_mode program_mode_value = {CLEAR, 0, 0};
    get_program_mode(argc, argv, &program_mode_value);

    FILE *fp;
    fp = fopen(conf_file_location, "r");
    if (fp == NULL) {
        printf("Cannot open conf file!\n");
        exit(EXIT_FAILURE);
    }
    long bram_address_offset = get_address_offset(fp);
    long bram_highest_address = get_highest_address(fp);
//    printf(
//            "conf file location: %s, program mode %d, offset: %ld, size: %ld\n",
//            conf_file_location,
//            program_mode_value.mode,
//            program_mode_value.offset,
//            program_mode_value.size
//    );
//    print_help(argv[0]);
}

void read() {

}
