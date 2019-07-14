//
// Created by andrzej on 23.06.19.
//

#ifndef BRAM_CONTROLLER_PROJECT_CLEAR_COMMAND_FACTORY_HPP
#define BRAM_CONTROLLER_PROJECT_CLEAR_COMMAND_FACTORY_HPP

#include <string>
#include "clear_command.hpp"
#include "clear_slient_command.hpp"
#include "clear_verbose_command.hpp"


class ClearCommandFactory {
private:
    const bool isSilent;
    const std::string &addressString;
    const std::string &numOfWordsToClearString;

public:
    explicit ClearCommandFactory(bool isSilent, std::string &address, std::string &numOfWordsToClear)
            : isSilent(isSilent), addressString(address), numOfWordsToClearString(numOfWordsToClear) {
    }

    std::shared_ptr<ProgramCommand> create() {
        std::shared_ptr<ProgramCommand> command = nullptr;
        uint address = 0;
        uint numOfWordsToClear = 0;
        if (isSilent) {
            address = std::stol(addressString);
            numOfWordsToClear = std::stol(numOfWordsToClearString);
            command = std::shared_ptr<ProgramCommand>(new ClearSilentCommand(address, numOfWordsToClear));
        } else {
            address = std::stol(addressString, nullptr, 16);
            numOfWordsToClear = std::stol(numOfWordsToClearString, nullptr, 16);
            command = std::shared_ptr<ProgramCommand>(new ClearVerboseCommand(address, numOfWordsToClear));
        }
        return command;
    }
};


#endif //BRAM_CONTROLLER_PROJECT_CLEAR_COMMAND_FACTORY_HPP
