//
// Created by andrzej on 16.06.19.
//

#ifndef BRAM_CONTROLLER_READ_COMMAND_VERBOSE_HPP
#define BRAM_CONTROLLER_READ_COMMAND_VERBOSE_HPP


#include <cstdio>
#include "read_command.hpp"

static const char* HEX_VALUES = "0123456789ABCDEF";

class ReadVerboseCommand : public ReadCommand {
public:
    ReadVerboseCommand(uint address, uint numOfWordsToRead): ReadCommand(address, numOfWordsToRead) {}
private:
    int read() override {
        printf("reading %u words from address: 0x%X\n", numOfWordsToRead, address);
        uint *memory;
        try {
            memory = openMemory(address, numOfWordsToRead);
        } catch (const MemoryException &e) {
            printf("cannot open memory block for address: 0x%X, cause: %s\n", address, e.what());
            return 1;
        }
        char *hexWord;
        for (int i = 0; i < numOfWordsToRead; ++i) {
            hexWord = uintToHex(memory[i]);
            printf("value for address: 0x%X is 0x%s\n", address + i * 4, hexWord);
            delete[] hexWord;
        }
        closeMemory(memory);
        return 0;
    }
    char* uintToHex(uint word) {
        char *values = new char[8];
        for (int i = 7; i >= 0; --i) {
            char value = (word >> (i * 4)) & 0xF;
            values[7 - i] = HEX_VALUES[value];
        }
        return values;
    }
};


#endif //BRAM_CONTROLLER_READ_COMMAND_VERBOSE_HPP
