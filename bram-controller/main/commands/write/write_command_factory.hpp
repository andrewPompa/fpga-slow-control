//
// Created by andrzej on 23.06.19.
//

#ifndef BRAM_CONTROLLER_PROJECT_WRITE_COMMAND_FACTORY_HPP
#define BRAM_CONTROLLER_PROJECT_WRITE_COMMAND_FACTORY_HPP


#include <string>
#include "write_command.hpp"
#include "write_silent_command.hpp"
#include "write_verbose_command.hpp"

class WriteCommandFactory {
private:
    const bool isSilent;
    const std::string & addressString;
    const std::string & numOfWordsToWriteString;
    const std::string & valueToWriteString;

public:
    explicit WriteCommandFactory(bool isSilent, std::string &address, std::string &numOfWordsToWrite, std::string &valueToWrite)
            : isSilent(isSilent), addressString(address), numOfWordsToWriteString(numOfWordsToWrite), valueToWriteString(valueToWrite) {
    }

    WriteCommand * create() {
        WriteCommand * command = nullptr;
        uint address = 0;
        uint numOfWordsToRead = 0;
        if (isSilent) {
            address = std::stol(addressString);
            numOfWordsToRead = std::stol(numOfWordsToWriteString);
            uint* wordsToWrite = getValueFromBase64(valueToWriteString);
            command = static_cast<WriteCommand*> (new WriteSilentCommand(address, numOfWordsToRead, wordsToWrite));
        } else {
            address = std::stol(addressString, nullptr, 16);
            numOfWordsToRead = std::stol(numOfWordsToWriteString, nullptr, 16);
            uint* wordsToWrite = getValueToWriteFromHexString(valueToWriteString);
            command = static_cast<WriteCommand*> (new WriteVerboseCommand(address, numOfWordsToRead, wordsToWrite));
        }
        return command;
    }

private:
    uint* getValueToWriteFromHexString(const std::string &basicString) {
        return nullptr;
    }

    uint *getValueFromBase64(const std::string &basicString) {
        return nullptr;
    }
};


#endif //BRAM_CONTROLLER_PROJECT_WRITE_COMMAND_FACTORY_HPP
