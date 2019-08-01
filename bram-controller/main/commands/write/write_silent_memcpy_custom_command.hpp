//
// Created by andrzej on 01.08.19.
//

#ifndef BRAM_CONTROLLER_PROJECT_WRITE_SILENT_MEMCPY_CUSTOM_COMMAND_HPP
#define BRAM_CONTROLLER_PROJECT_WRITE_SILENT_MEMCPY_CUSTOM_COMMAND_HPP

#include <string.h>
#include <utils/memcpy_custom.h>
#include "write_command.hpp"

class WriteSilentMemcpyCustomCommand : public WriteCommand {
public:
    explicit WriteSilentMemcpyCustomCommand(uint address, uint numOfWordsToWrite, std::shared_ptr<uint>& words) : WriteCommand(address, numOfWordsToWrite, words) {
    }

private:
    int write() override {
        uint * memory;
        try {
            memory = openMemory(address, numOfWordsToWrite);
        } catch (const MemoryException &e) {
            return 1;
        }
        memcpyCustom(memory, words.get(), numOfWordsToWrite * 4);
        closeMemory(memory);
        return 0;
    }
};


#endif //BRAM_CONTROLLER_PROJECT_WRITE_SILENT_MEMCPY_CUSTOM_COMMAND_HPP
