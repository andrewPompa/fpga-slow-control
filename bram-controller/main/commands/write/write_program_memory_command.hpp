//
// Created by andrzej on 24.07.19.
//

#ifndef BRAM_CONTROLLER_PROJECT_WRITE_PROGRAM_MEMORY_COMMAND_HPP
#define BRAM_CONTROLLER_PROJECT_WRITE_PROGRAM_MEMORY_COMMAND_HPP


#include "write_command.hpp"

class WriteProgramMemoryCommand : public WriteCommand {
private:
    uint* memory;
public:
    explicit WriteProgramMemoryCommand(uint * programMemory, uint numOfWordsToWrite, std::shared_ptr<uint>& words) : WriteCommand(0, numOfWordsToWrite, words) {
        this->memory = programMemory;
    }
private:
    int write() override {
        for (int i = 0; i < numOfWordsToWrite; ++i) {
            memory[i] = words.get()[i];
        }
        return 0;
    }
};


#endif //BRAM_CONTROLLER_PROJECT_WRITE_PROGRAM_MEMORY_COMMAND_HPP
