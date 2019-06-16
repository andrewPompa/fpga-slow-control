//
// Created by andrzej on 16.06.19.
//

#ifndef BRAM_CONTROLLER_READ_COMMAND_HPP
#define BRAM_CONTROLLER_READ_COMMAND_HPP


#include "../program_command.hpp"

class ReadCommand: public ProgramCommand {
public:
    int execute() override {
        return read();
    }

protected:
    unsigned int address{};
    unsigned int offset{};
    unsigned int num_of_words_to_read{};
    unsigned int *read_words{};
    virtual int read() = 0;
};


#endif //BRAM_CONTROLLER_READ_COMMAND_HPP
