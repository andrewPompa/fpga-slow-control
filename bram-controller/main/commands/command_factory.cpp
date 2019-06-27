
#include <cstdio>
#include <iostream>
#include "command_factory.hpp"
#include "help/help_verbose_command.hpp"
#include "read/read_silent_command.hpp"
#include "write/write_verbose_command.hpp"
#include "write/write_silent_command.hpp"
#include "clear/clear_slient_command.hpp"
#include "clear/clear_verbose_command.hpp"
#include "help/help_silent_command.hpp"
#include "read/read_verbose_command.hpp"
#include "clear/clear_command.hpp"
#include "read/read_command_factory.hpp"
#include "write/write_command_factory.hpp"
#include "clear/clear_command_factory.hpp"

using namespace std;

CommandFactory::CommandFactory(std::vector<std::string> *args) {
    this->args = new vector<string>(*args);
    this->args->erase(this->args->begin());
}

ProgramCommand *CommandFactory::create() {
    bool isHelp = hasArgument("-h") || hasArgument("--help");
    if (isHelp) {
        return static_cast<ProgramCommand *> (new HelpVerboseCommand());
    }

    bool isSilent = hasArgument("-s") || hasArgument("--silent");
    bool isRead = hasArgument("-r") || hasArgument("--read");
    bool isWrite = hasArgument("-w") || hasArgument("--write");
    bool isClear = hasArgument("-c") || hasArgument("--clear");
    if (isRead + isWrite + isClear > 1) {
        throw std::invalid_argument("too many operations selected in arguments");
    }
    ProgramCommand *programCommand = nullptr;
    if (isRead) {
        programCommand = createReadCommand(isSilent);
    } else if (isWrite) {
        programCommand = createWriteCommand(isSilent);
    } else if (isClear) {
        programCommand = createClearCommand(isSilent);
    }
    return programCommand;
}

ReadCommand *CommandFactory::createReadCommand(bool isSilent) {
    int index = findOptionIndex("-r");
    if (index == -1) {
        index = findOptionIndex("--read");
    }
    if (this->args->size() < 2) {
        throw std::invalid_argument("Not enough options for read command");
    }
    ReadCommandFactory readCommandFactory(isSilent, this->args->at(index + 1), this->args->at(index + 2));
    return readCommandFactory.create();
}

WriteCommand *CommandFactory::createWriteCommand(bool isSilent) {
    int index = findOptionIndex("-w");
    if (index == -1) {
        index = findOptionIndex("--write");
    }
    if (this->args->size() < 3) {
        throw std::invalid_argument("Not enough options for write command");
    }
    WriteCommandFactory writeCommandFactory(isSilent, this->args->at(index + 1), this->args->at(index + 2), this->args->at(index + 3));
    return writeCommandFactory.create();
}

ClearCommand *CommandFactory::createClearCommand(bool isSilent) {
    int index = findOptionIndex("-c");
    if (index == -1) {
        index = findOptionIndex("--clear");
    }
    if (this->args->size() < 3) {
        throw std::invalid_argument("Not enough options for clear command");
    }
    ClearCommandFactory clearCommandFactory(isSilent, this->args->at(index + 1), this->args->at(index + 2));
    return clearCommandFactory.create();
}

bool CommandFactory::hasArgument(const string &value) {
    for (const string &argument: *args) {
        if (argument == value) {
            return true;
        }
    }
    return false;
}

int CommandFactory::findOptionIndex(const std::string &value) {
    for (int i = 0; i < args->size(); ++i) {
        if (args->at(i) == value) {
            return i;
        }
    }
    return -1;
}

