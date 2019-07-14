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
private:
    std::vector <std::string>& args;
public:
    explicit CommandFactory(std::vector<std::string> & args);

    std::shared_ptr<ProgramCommand> create();

private:
    std::shared_ptr<ProgramCommand> validateArgumentsAndCreate(bool isSilent);

    std::shared_ptr<ProgramCommand> createReadCommand(bool isSilent);
    std::shared_ptr<ProgramCommand> createWriteCommand(bool isSilent);
    std::shared_ptr<ProgramCommand> createClearCommand(bool isSilent);

    int findOptionIndex(const std::string &value);
    bool hasArgument(const std::string &value);
};


#endif //BRAM_CONTROLLER_COMMAND_FACTORY_HPP
