
#include <cstdio>
#include "command_factory.hpp"

ProgramCommand *CommandFactory::create() {
    if (isReadCommand()) {
        return readCommandFactory.create(argc, argv);
    }
    if (isWriteCommand()) {
        return writeCommandFactory.create(argc, argv);
    }
    return nullptr;
}

bool CommandFactory::isWriteCommand() {
    for (int i = 0; i < argc; ++i) {
        printf("Hello: %s\n", argv[i]);
    }
    return false;
}

bool CommandFactory::isReadCommand() {
    for (int i = 0; i < argc; ++i) {
        printf("Hello: %s\n", argv[i]);
    }
    return false;
}
