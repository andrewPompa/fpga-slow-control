//
// Created by andrzej on 20.06.19.
//

#ifndef BRAM_CONTROLLER_PROJECT_HELP_SILENT_COMMAND_HPP
#define BRAM_CONTROLLER_PROJECT_HELP_SILENT_COMMAND_HPP


#include "../program_command.hpp"

class HelpSilentCommand: public ProgramCommand {
public:
    int execute() override {
        printf("HelpSilentCommand\n");
        return 0;
    }
};


#endif //BRAM_CONTROLLER_PROJECT_HELP_SILENT_COMMAND_HPP
