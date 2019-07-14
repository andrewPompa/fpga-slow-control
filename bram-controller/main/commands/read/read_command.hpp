//
// Created by andrzej on 16.06.19.
//

#ifndef BRAM_CONTROLLER_READ_COMMAND_HPP
#define BRAM_CONTROLLER_READ_COMMAND_HPP


#include "../program_command.hpp"

class ReadCommand: public ProgramCommand {
public:
    explicit ReadCommand(uint address, uint numOfWordsToRead): address(address), numOfWordsToRead(numOfWordsToRead) {}

    int execute() override {
        return read();
    }

protected:
    unsigned int address{};
    unsigned int numOfWordsToRead{};
    virtual int read() = 0;
};


#endif //BRAM_CONTROLLER_READ_COMMAND_HPP
