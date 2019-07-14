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

class WriteCommandFactory {
private:
    const bool isSilent;
    const std::string &addressString;
    const std::string &numOfWordsToWriteString;
    std::vector<std::string> &writeWords;

public:
    explicit WriteCommandFactory(bool isSilent, std::string &address, std::string &numOfWordsToWrite,
                                 std::vector<std::string> &writeWords)
            : isSilent(isSilent), addressString(address), numOfWordsToWriteString(numOfWordsToWrite),
              writeWords(writeWords) {
    }

    std::shared_ptr<ProgramCommand> create() {
        std::shared_ptr<ProgramCommand> command = nullptr;
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
            std::shared_ptr<uint> bytesToWrite = getValueFromBase64(writeWords.at(0));
            command = std::shared_ptr<ProgramCommand>(new WriteSilentCommand(address, numOfWordsToWrite, bytesToWrite));
        } else {
            HexArgumentReader hexArgumentReader;
            address = hexArgumentReader.readWord(addressString);
            numOfWordsToWrite = hexArgumentReader.readWord(numOfWordsToWriteString);
            if (numOfWordsToWrite != writeWords.size()) {
                throw std::invalid_argument("num of words is different than sent words to write");
            }
            std::shared_ptr<uint> valueToWrite(new uint[numOfWordsToWrite]);
            for (int i = 0; i < numOfWordsToWrite; ++i) {
                valueToWrite.get()[i] = hexArgumentReader.readWord(writeWords.at(i));
            }
            command = std::shared_ptr<ProgramCommand>(
                    new WriteVerboseCommand(address, numOfWordsToWrite, valueToWrite));
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
