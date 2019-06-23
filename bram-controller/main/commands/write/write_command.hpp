//
// Created by andrzej on 16.06.19.
//

#ifndef BRAM_CONTROLLER_WRITE_COMMAND_HPP
#define BRAM_CONTROLLER_WRITE_COMMAND_HPP

#include "../program_command.hpp"

class WriteCommand : public ProgramCommand {
private:
    const uint address;
    const uint words;
    const uint *bytes;
public:
    explicit WriteCommand(uint address, uint words, const uint *bytes) : address(address), words(words), bytes(bytes) {}

    int execute() override {
        return write();
    }

protected:
    virtual int write() = 0;
};

#endif //BRAM_CONTROLLER_WRITE_COMMAND_HPP
