//
// Created by andrzej on 16.06.19.
//

#ifndef BRAM_CONTROLLER_READ_COMMAND_VERBOSE_HPP
#define BRAM_CONTROLLER_READ_COMMAND_VERBOSE_HPP


#include <cstdio>
#include "read_command.hpp"

class ReadCommnadVerbose : public ReadCommand {
public:
    int read() override {
        printf("Read Command from verbose\n");
        return 0;
    }
};


#endif //BRAM_CONTROLLER_READ_COMMAND_VERBOSE_HPP
