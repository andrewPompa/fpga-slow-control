//
// Created by andrzej on 16.06.19.
//

#ifndef BRAM_CONTROLLER_WRITE_COMMAND_HPP
#define BRAM_CONTROLLER_WRITE_COMMAND_HPP

#include "../program_command.hpp"

class WriteCommand : public ProgramCommand {
public:
    int execute() override  {
        return write();
    }
protected:
    virtual int write() = 0;
    unsigned int address{};
    unsigned int words{};
    unsigned int offset{};
    unsigned int *bytes{};
};

#endif //BRAM_CONTROLLER_WRITE_COMMAND_HPP
