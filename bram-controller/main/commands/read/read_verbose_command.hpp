//
// Created by andrzej on 16.06.19.
//

#ifndef BRAM_CONTROLLER_READ_COMMAND_VERBOSE_HPP
#define BRAM_CONTROLLER_READ_COMMAND_VERBOSE_HPP


#include <cstdio>
#include "read_command.hpp"

class ReadVerboseCommand : public ReadCommand {
public:
    ReadVerboseCommand(uint address, uint numOfWordsToRead): ReadCommand(address, numOfWordsToRead) {}
private:
    int read() override {
        printf("Read Command from verbose: address: %u, value: %u\n", address, numOfWordsToRead);
        return 0;
    }
};


#endif //BRAM_CONTROLLER_READ_COMMAND_VERBOSE_HPP
