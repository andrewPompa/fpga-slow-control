
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

CommandFactory::CommandFactory(std::vector<std::string> & args): args(args) {
    args = vector<string>(args);
    this->args.erase(this->args.begin());
}

std::shared_ptr<ProgramCommand> CommandFactory::create() {
    bool isSilent = hasArgument("-s") || hasArgument("--silent");
    try {
        return validateArgumentsAndCreate(isSilent);
    } catch (std::invalid_argument &e) {
        if (!isSilent) {
            printf("cannot create command: %s\n", e.what());
        }
        return nullptr;
    }
}

std::shared_ptr<ProgramCommand> CommandFactory::validateArgumentsAndCreate(bool isSilent) {
    bool isHelp = hasArgument("-h") || hasArgument("--help");
    if (isHelp) {
        return std::shared_ptr<ProgramCommand>(new HelpVerboseCommand());
    }

    bool isRead = hasArgument("-r") || hasArgument("--read");
    bool isWrite = hasArgument("-w") || hasArgument("--write");
    bool isClear = hasArgument("-c") || hasArgument("--clear");
    if (isRead + isWrite + isClear > 1) {
        throw std::invalid_argument("too many operations selected in arguments");
    } else if (isRead + isWrite + isClear == 0) {
        throw std::invalid_argument("no operations selected");
    }

    std::shared_ptr<ProgramCommand> programCommand = nullptr;
    if (isRead) {
        programCommand = createReadCommand(isSilent);
    } else if (isWrite) {
        programCommand = createWriteCommand(isSilent);
    } else if (isClear) {
        programCommand = createClearCommand(isSilent);
    }
    return programCommand;
}

std::shared_ptr<ProgramCommand> CommandFactory::createReadCommand(bool isSilent) {
    int index = findOptionIndex("-r");
    if (index == -1) {
        index = findOptionIndex("--read");
    }
    if (this->args.size() < 3) {
        throw std::invalid_argument("Not enough options for read command");
    }
    ReadCommandFactory readCommandFactory(isSilent, this->args.at(index + 1), this->args.at(index + 2));
    return readCommandFactory.create();
}

std::shared_ptr<ProgramCommand> CommandFactory::createWriteCommand(bool isSilent) {
    int index = findOptionIndex("-w");
    if (index == -1) {
        index = findOptionIndex("--write");
    }
    if (this->args.size() < 4) {
        throw std::invalid_argument("Not enough options for write command");
    }
    std::vector<std::string> writeWords(args.begin() + index + 3, args.end());
    WriteCommandFactory writeCommandFactory(isSilent, args.at(index + 1), args.at(index + 2), writeWords);
    return writeCommandFactory.create();
}

std::shared_ptr<ProgramCommand> CommandFactory::createClearCommand(bool isSilent) {
    int index = findOptionIndex("-c");
    if (index == -1) {
        index = findOptionIndex("--clear");
    }
    if (this->args.size() < 3) {
        throw std::invalid_argument("Not enough options for clear command");
    }
    ClearCommandFactory clearCommandFactory(isSilent, this->args.at(index + 1), this->args.at(index + 2));
    return clearCommandFactory.create();
}

bool CommandFactory::hasArgument(const string &value) {
    for (const string &argument: args) {
        if (argument == value) {
            return true;
        }
    }
    return false;
}

int CommandFactory::findOptionIndex(const std::string &value) {
    for (int i = 0; i < args.size(); ++i) {
        if (args.at(i) == value) {
            return i;
        }
    }
    return -1;
}
