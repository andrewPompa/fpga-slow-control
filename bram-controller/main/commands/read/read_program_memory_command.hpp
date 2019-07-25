//
// Created by andrzej on 24.07.19.
//

#ifndef BRAM_CONTROLLER_PROJECT_READ_PROGRAM_MEMORY_COMMAND_HPP
#define BRAM_CONTROLLER_PROJECT_READ_PROGRAM_MEMORY_COMMAND_HPP


#include <base64/base_64.hpp>
#include "read_command.hpp"

class ReadProgramMemoryCommand : public ReadCommand {
private:
    u_char *memory;
public:
    ReadProgramMemoryCommand(uint *memory, uint numOfWordsToRead) : ReadCommand(0, numOfWordsToRead) {
        this->memory = reinterpret_cast<u_char *>(memory);
    }

private:
    int read() override {
        for (int i = 0; i < numOfWordsToRead * 4; ++i) {}
        return 0;
    }

};


#endif //BRAM_CONTROLLER_PROJECT_READ_PROGRAM_MEMORY_COMMAND_HPP
