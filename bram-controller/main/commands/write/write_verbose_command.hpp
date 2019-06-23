//
// Created by andrzej on 16.06.19.
//

#ifndef BRAM_CONTROLLER_WRITE_COMMAND_VERBOSE_HPP
#define BRAM_CONTROLLER_WRITE_COMMAND_VERBOSE_HPP


#include "write_command.hpp"

class WriteVerboseCommand : public WriteCommand {
public:
    explicit WriteVerboseCommand(uint address, uint words, const uint *bytes) : WriteCommand(address, words, bytes) {}
private:
    int write() override {
        return 0;
    }
};


#endif //BRAM_CONTROLLER_WRITE_COMMAND_VERBOSE_HPP
