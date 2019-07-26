//
// Created by andrzej on 16.06.19.
//

#ifndef BRAM_CONTROLLER_WRITE_COMMAND_APPLICATION_HPP
#define BRAM_CONTROLLER_WRITE_COMMAND_APPLICATION_HPP

#include <string.h>
#include "write_command.hpp"

class WriteSilentCommand : public WriteCommand {
public:
    explicit WriteSilentCommand(uint address, uint numOfWordsToWrite, std::shared_ptr<uint>& words) : WriteCommand(address, numOfWordsToWrite, words) {
    }

private:
    int write() override {
        uint * memory;
        try {
            memory = openMemory(address, numOfWordsToWrite);
        } catch (const MemoryException &e) {
            return 1;
        }
        for (int i = 0; i < numOfWordsToWrite; ++i) {
            memory[i] = words.get()[i];
        }
        closeMemory(memory);
        return 0;
    }
};

#endif //BRAM_CONTROLLER_WRITE_COMMAND_APPLICATION_HPP
