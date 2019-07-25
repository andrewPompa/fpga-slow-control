//
// Created by andrzej on 25.07.19.
//

#ifndef BRAM_CONTROLLER_PROJECT_PERFORMANCE_CHECK_READ_COMMAND_HPP
#define BRAM_CONTROLLER_PROJECT_PERFORMANCE_CHECK_READ_COMMAND_HPP


#include "read_command.hpp"
#include <iostream>

class PerformanceCheckReadCommand : public ReadCommand {
public:
    explicit PerformanceCheckReadCommand(uint address, uint numOfWordsToRead) : ReadCommand(address, numOfWordsToRead) {}

private:
    int read() override {
        u_char *memory;
        try {
            memory = (u_char *) openMemory(address, numOfWordsToRead);
        } catch (const MemoryException &e) {
            throw std::invalid_argument("cannot open memory!");
        }
        for (int i = 0; i < numOfWordsToRead * 4; ++i) {
        }
        closeMemory(reinterpret_cast<uint *>(memory));
        return 0;
    }
};


#endif //BRAM_CONTROLLER_PROJECT_PERFORMANCE_CHECK_READ_COMMAND_HPP
