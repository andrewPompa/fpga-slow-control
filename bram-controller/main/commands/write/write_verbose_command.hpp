//
// Created by andrzej on 16.06.19.
//

#ifndef BRAM_CONTROLLER_WRITE_COMMAND_VERBOSE_HPP
#define BRAM_CONTROLLER_WRITE_COMMAND_VERBOSE_HPP


#include "write_command.hpp"
#include <memory>

class WriteVerboseCommand : public WriteCommand {
public:
    explicit WriteVerboseCommand(uint address, uint numOfWordsToWrite, std::shared_ptr<uint>& words) : WriteCommand(address, numOfWordsToWrite, words) {}
private:
    int write() override {
        uint * memory;
        try {
            memory = openMemory(address, numOfWordsToWrite);
        } catch (const MemoryException &e) {
            printf("exception occur during opening memory for address: %u, cause: %s\n", address, e.what());
            return 1;
        }
        for (int i = 0; i < numOfWordsToWrite; ++i) {
            printf("writing word: 0x%X to address: 0x%X\n", words.get()[i], address + i * 4);
            memory[i] = words.get()[i];
        }
        printf("wrote properly %u words for address: 0x%X\n", numOfWordsToWrite, address);
        closeMemory(memory);
        return 0;
    }
};


#endif //BRAM_CONTROLLER_WRITE_COMMAND_VERBOSE_HPP
