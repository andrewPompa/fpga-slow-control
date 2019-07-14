//
// Created by andrzej on 16.06.19.
//

#ifndef BRAM_CONTROLLER_WRITE_COMMAND_HPP
#define BRAM_CONTROLLER_WRITE_COMMAND_HPP

#include "../program_command.hpp"
#include <memory>

class WriteCommand : public ProgramCommand {
protected:
    const uint address;
    const uint numOfWordsToWrite;
    std::shared_ptr<uint> words;
public:
    explicit WriteCommand(uint address, uint numOfWordsToWrite, std::shared_ptr<uint> words) : address(address), numOfWordsToWrite(numOfWordsToWrite), words(std::move(words)) {}

    int execute() override {
        return write();
    }

protected:
    virtual int write() = 0;
};

#endif //BRAM_CONTROLLER_WRITE_COMMAND_HPP