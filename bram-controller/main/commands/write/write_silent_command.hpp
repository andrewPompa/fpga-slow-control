//
// Created by andrzej on 16.06.19.
//

#ifndef BRAM_CONTROLLER_WRITE_COMMAND_APPLICATION_HPP
#define BRAM_CONTROLLER_WRITE_COMMAND_APPLICATION_HPP


#include "write_command.hpp"

class WriteSilentCommand : public WriteCommand {
public:
    explicit WriteSilentCommand(uint address, uint numOfWordsToWrite, const uint *words) : WriteCommand(address, numOfWordsToWrite, words) {}

private:
    int write() override {
        uint * memory;
        try {
            memory = openMemory(address, numOfWordsToWrite);
        } catch (const MemoryException &e) {
            return 1;
        }
        for (int i = 0; i < numOfWordsToWrite; ++i) {
            memory[i] = words[i];
        }
        return 0;
    }
};

#endif //BRAM_CONTROLLER_WRITE_COMMAND_APPLICATION_HPP
