//
// Created by andrzej on 23.06.19.
//

#ifndef BRAM_CONTROLLER_PROJECT_READ_COMMAND_FACTORY_HPP
#define BRAM_CONTROLLER_PROJECT_READ_COMMAND_FACTORY_HPP


#include <string>
#include "read_command.hpp"

class ReadCommandFactory {
private:
    const bool isSilent;
    const std::string & addressString;
    const std::string & numOfWordsToReadString;

public:
    explicit ReadCommandFactory(bool isSilent, std::string &address, std::string &numOfWordsToRead)
            : isSilent(isSilent), addressString(address), numOfWordsToReadString(numOfWordsToRead) {
    }
    ReadCommand * create() {
        ReadCommand * command = nullptr;
        uint address = 0;
        uint numOfWordsToRead = 0;
        if (isSilent) {
            address = std::stol(addressString);
            numOfWordsToRead = std::stol(numOfWordsToReadString);
            command = static_cast<ReadCommand*> (new ReadSilentCommand(address, numOfWordsToRead));
        } else {
            address = std::stol(addressString, nullptr, 16);
            numOfWordsToRead = std::stol(numOfWordsToReadString, nullptr, 16);
            command = static_cast<ReadCommand*> (new ReadVerboseCommand(address, numOfWordsToRead));
        }
        return command;
    }
};


#endif //BRAM_CONTROLLER_PROJECT_READ_COMMAND_FACTORY_HPP
