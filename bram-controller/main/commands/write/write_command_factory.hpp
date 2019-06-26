//
// Created by andrzej on 23.06.19.
//

#ifndef BRAM_CONTROLLER_PROJECT_WRITE_COMMAND_FACTORY_HPP
#define BRAM_CONTROLLER_PROJECT_WRITE_COMMAND_FACTORY_HPP


#include <string>
#include <regex>
#include "write_command.hpp"
#include "write_silent_command.hpp"
#include "write_verbose_command.hpp"

const std::regex hexRegexWithZeroPrefix("0x[0-9A-F]+");

class WriteCommandFactory {
private:
    const bool isSilent;
    const std::string & addressString;
    const std::string & numOfWordsToWriteString;
    std::string & valueToWriteString;

public:
    explicit WriteCommandFactory(bool isSilent, std::string &address, std::string &numOfWordsToWrite, std::string &valueToWrite)
            : isSilent(isSilent), addressString(address), numOfWordsToWriteString(numOfWordsToWrite), valueToWriteString(valueToWrite) {
    }
    WriteCommand * create() {
        WriteCommand * command = nullptr;
        uint address = 0;
        uint numOfWordsToWrite = 0;
        if (isSilent) {
            address = std::stol(addressString);
            numOfWordsToWrite = std::stol(numOfWordsToWriteString);
            std::vector<u_char> bytesToWrite = getValueFromBase64(valueToWriteString);
            if (bytesToWrite.size() / 4 != numOfWordsToWrite) {
                return nullptr;
            }
            uint *words = (uint *) &bytesToWrite[0];
            command = static_cast<WriteCommand*> (new WriteSilentCommand(address, numOfWordsToWrite, words));
        } else {
            address = std::stol(addressString, nullptr, 16);
            numOfWordsToWrite = std::stol(numOfWordsToWriteString, nullptr, 16);
            if (valueToWriteString.size() % 8 != 0 || valueToWriteString.size() / 8 != numOfWordsToWrite) {
                printf("sent words to write do not have 32 bits length, or value is not equal to specified num of words\n");
                return nullptr;
            }
            uint* wordsToWrite = getValueToWriteFromHexString(valueToWriteString, numOfWordsToWrite);
            command = static_cast<WriteCommand*> (new WriteVerboseCommand(address, numOfWordsToWrite, wordsToWrite));
        }
        return command;
    }

private:
    uint* getValueToWriteFromHexString(std::string &basicString, uint numOfWordsToRead) {
        if (std::regex_match(basicString, hexRegexWithZeroPrefix)) {
            basicString = basicString.erase(0, 2);
        }
        uint *valueToWrite = new uint[numOfWordsToRead];
        for (int i = 0; i < numOfWordsToRead; ++i) {
            valueToWrite[i] = std::stol(basicString.substr(i * 8, 8), nullptr, 16);
        }
        return valueToWrite;
    }

    std::vector<u_char> getValueFromBase64(const std::string &basicString) {
        Base64 base64;
        return base64.decode(basicString);
    }
};


#endif //BRAM_CONTROLLER_PROJECT_WRITE_COMMAND_FACTORY_HPP
