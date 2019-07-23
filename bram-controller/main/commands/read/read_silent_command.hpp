//
// Created by andrzej on 16.06.19.
//

#ifndef BRAM_CONTROLLER_READ_COMMAND_APPLICATION_HPP
#define BRAM_CONTROLLER_READ_COMMAND_APPLICATION_HPP

#include <cstdio>
#include "read_command.hpp"
#include "../../base64/base_64.hpp"
#include <iostream>

class ReadSilentCommand : public ReadCommand {
public:
    ReadSilentCommand(uint address, uint numOfWordsToRead) : ReadCommand(address, numOfWordsToRead) {}
    
    std::string readValue() {
        u_char *memory;
        try {
            memory = (u_char *) openMemory(address, numOfWordsToRead);
        } catch (const MemoryException &e) {
            return std::string();
        }
        Base64 base64;
        std::string value = base64.encode(memory, numOfWordsToRead * 4);
        closeMemory(reinterpret_cast<uint *>(memory));
        return value;
    }
private:
    int read() override {
        const std::string &value = readValue();
        if (value.empty()) {
            return 1;
        }
        printf("%s\n", value.c_str());
        return 0;
    }
};

#endif //BRAM_CONTROLLER_READ_COMMAND_APPLICATION_HPP
