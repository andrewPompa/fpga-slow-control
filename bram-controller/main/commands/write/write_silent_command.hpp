//
// Created by andrzej on 16.06.19.
//

#ifndef BRAM_CONTROLLER_WRITE_COMMAND_APPLICATION_HPP
#define BRAM_CONTROLLER_WRITE_COMMAND_APPLICATION_HPP


#include "write_command.hpp"

class WriteSilentCommand : public WriteCommand {
public:
    explicit WriteSilentCommand(uint address, uint words, const uint *bytes) : WriteCommand(address, words, bytes) {}

private:
    int write() override {
        return 0;
    }
};

#endif //BRAM_CONTROLLER_WRITE_COMMAND_APPLICATION_HPP
