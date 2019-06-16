//
// Created by andrzej on 16.06.19.
//

#ifndef BRAM_CONTROLLER_COMMAND_FACTORY_HPP
#define BRAM_CONTROLLER_COMMAND_FACTORY_HPP


#include "program_command.hpp"
#include "read/read_command_factory.hpp"
#include "write/write_command_factory.hpp"

class CommandFactory {
public:
    CommandFactory(int argc, char **argv) {
        this->argc = argc;
        this->argv = argv;
    }

    ProgramCommand * create() {
        if (isRead()) {
            return readCommandFactory.create(argc, argv);
        }
        if (isWrite()) {
            return writeCommandFactory.create(argc, argv);
        }
        return nullptr;
    }
private:
    int argc;
    char **argv;
    ReadCommandFactory readCommandFactory;
    WriteCommandFactory writeCommandFactory;

    bool isWrite() {
        return false;
    }

    bool isRead() {
        return false;
    }
};


#endif //BRAM_CONTROLLER_COMMAND_FACTORY_HPP
