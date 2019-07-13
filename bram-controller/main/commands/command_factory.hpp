//
// Created by andrzej on 16.06.19.
//

#ifndef BRAM_CONTROLLER_COMMAND_FACTORY_HPP
#define BRAM_CONTROLLER_COMMAND_FACTORY_HPP

#include <vector>
#include "program_command.hpp"
#include "read/read_command.hpp"
#include "write/write_command.hpp"
#include "clear/clear_command.hpp"

class CommandFactory {
public:
    explicit CommandFactory(std::vector<std::string> * args);

    ProgramCommand * create();
private:
    std::vector <std::string> * args;

    ProgramCommand * validateArgumentsAndCreate(bool isSilent);

    ReadCommand *createReadCommand(bool isSilent);
    WriteCommand *createWriteCommand(bool isSilent);
    ClearCommand *createClearCommand(bool isSilent);

    int findOptionIndex(const std::string &value);
    bool hasArgument(const std::string &value);
};


#endif //BRAM_CONTROLLER_COMMAND_FACTORY_HPP
