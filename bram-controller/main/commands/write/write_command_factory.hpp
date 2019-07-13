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
#include "../../utils/hex_argument_reader.hpp"
#include <climits>

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
            if (std::stol(addressString) > UINT_MAX) {
                throw std::invalid_argument("address has to be 32 bit number");
            }
            if (std::stol(numOfWordsToWriteString) > UINT_MAX) {
                throw std::invalid_argument("num of words has to be 32 bit number");
            }
            address = std::stol(addressString);
            numOfWordsToWrite = std::stol(numOfWordsToWriteString);
            std::shared_ptr<uint> bytesToWrite = getValueFromBase64(valueToWriteString);
            command = static_cast<WriteCommand*> (new WriteSilentCommand(address, numOfWordsToWrite, bytesToWrite));
        } else {
            HexArgumentReader hexArgumentReader;
            address = hexArgumentReader.readWord(addressString);
            numOfWordsToWrite = hexArgumentReader.readWord(numOfWordsToWriteString);

            std::shared_ptr<uint> wordsToWrite = hexArgumentReader.readWords(valueToWriteString, numOfWordsToWrite);
            if (wordsToWrite == nullptr) {
                printf("sent words to write do not have 32 bits length, or value is not equal to specified num of words\n");
                return nullptr;
            }
            command = static_cast<WriteCommand*> (new WriteVerboseCommand(address, numOfWordsToWrite, wordsToWrite));
        }
        return command;
    }

private:
    std::shared_ptr<uint> getValueFromBase64(const std::string &basicString) {
        Base64 base64;
        return base64.decodeWords(basicString);
    }
};


#endif //BRAM_CONTROLLER_PROJECT_WRITE_COMMAND_FACTORY_HPP
