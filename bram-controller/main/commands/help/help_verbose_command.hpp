//
// Created by andrzej on 20.06.19.
//

#ifndef BRAM_CONTROLLER_PROJECT_HELP_VERBOSE_COMMAND_HPP
#define BRAM_CONTROLLER_PROJECT_HELP_VERBOSE_COMMAND_HPP


#include "../program_command.hpp"

class HelpVerboseCommand: public ProgramCommand {
public:
    int execute() override {
        printf("HelpVerboseCommand\n");
        return 0;
    }
};


#endif //BRAM_CONTROLLER_PROJECT_HELP_VERBOSE_COMMAND_HPP
