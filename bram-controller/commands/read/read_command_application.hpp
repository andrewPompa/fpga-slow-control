//
// Created by andrzej on 16.06.19.
//

#ifndef BRAM_CONTROLLER_READ_COMMAND_APPLICATION_HPP
#define BRAM_CONTROLLER_READ_COMMAND_APPLICATION_HPP

#include <cstdio>
#include "read_command.hpp"

class ReadCommandApplication : public ReadCommand {
    int read() override {
        printf("Read Command from application\n");
        return 0;
    }
};

#endif //BRAM_CONTROLLER_READ_COMMAND_APPLICATION_HPP
