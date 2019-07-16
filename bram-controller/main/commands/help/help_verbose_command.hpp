//
// Created by andrzej on 20.06.19.
//

#ifndef BRAM_CONTROLLER_PROJECT_HELP_VERBOSE_COMMAND_HPP
#define BRAM_CONTROLLER_PROJECT_HELP_VERBOSE_COMMAND_HPP


#include "../program_command.hpp"

class HelpVerboseCommand: public ProgramCommand {
private:
    std::string const & programName;

public:
    explicit HelpVerboseCommand(std::string const & programName): programName(programName) {}

    int execute() override {
        printf(
                "Program to manage FPGA memory. Usage: \n"
                "%s [-s|--silent] -r|-w|-c ARGS\n"
                "when program is in verbose mode (default) ARGS have to be provided as hex values (32bits) range 0x0 - 0xFFFFFFFF\n"
                "------------------------------\n"
                "-r|--read retrieve 32 bit words from memory\n"
                "ARGS for verbose(default): hex_address hex_num_of_words, eg. %s --read 0xA0000000 0xF read 15 words from address 0xA0000000. Output will be pretty printed words of memory\n"
                "ARGS for silent(for programs): address numOfWordsToRead, eg. %s --read 2684354560 15 read 15 words from address 0xA0000000. Output will be base64 encoded bytes\n"
                "------------------------------\n"
                "-w|--write put 32 bit words into memory\n"
                "ARGS for verbose(default): hex_address hex_num_of_words hex_word_1, hex_word_2, ...hex_word^numOfWords, eg. %s --read 0xB0000000 0x2 0xAABB 0xFFEEDDCC write words 0xAABB to 0xA0000000 and 0xFFEEDDCC 0xA0000004\n"
                "ARGS for silent(for programs): address numOfWordsToRead base64EncodedValue, eg. %s -w 2684354560 8 MDAxMTIyMzNBQUJCQ0NERDQ0NTU2Njc3RUVGRkFBQkI= write 8 words beginning from address 0xA0000000\n"
                "------------------------------\n"
                "-c|--clear clears memory\n"
                "ARGS for verbose(default): hex_address hex_num_of_words eg. %s -c 0xB0000000 0x2 put 0x0 into memory 0xA0000000 and 0xA0000004\n"
                "ARGS for silent(for programs): address numOfWordsToRead, eg. %s --clear 2684354560 8 clears 8 words beginning from address 0xA0000000\n",
                programName.c_str(), programName.c_str(), programName.c_str(), programName.c_str(), programName.c_str(), programName.c_str(), programName.c_str()
        );
        return 0;
    }
};

#endif //BRAM_CONTROLLER_PROJECT_HELP_VERBOSE_COMMAND_HPP
