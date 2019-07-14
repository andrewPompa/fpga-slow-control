//
// Created by andrzej on 23.06.19.
//

#ifndef BRAM_CONTROLLER_PROJECT_READ_COMMAND_FACTORY_HPP
#define BRAM_CONTROLLER_PROJECT_READ_COMMAND_FACTORY_HPP


#include <string>
#include <climits>
#include "read_command.hpp"
#include "../../utils/hex_argument_reader.hpp"

class ReadCommandFactory {
private:
    const bool isSilent;
    const std::string &addressString;
    const std::string &numOfWordsToReadString;

public:
    explicit ReadCommandFactory(bool isSilent, std::string &address, std::string &numOfWordsToRead)
            : isSilent(isSilent), addressString(address), numOfWordsToReadString(numOfWordsToRead) {
    }

    std::shared_ptr<ProgramCommand> create() {
        std::shared_ptr<ProgramCommand> command = nullptr;
        uint address = 0;
        uint numOfWordsToRead = 0;
        if (isSilent) {
            if (std::stol(addressString) > UINT_MAX) {
                throw std::invalid_argument("address has to be 32 bit number");
            }
            if (std::stol(numOfWordsToReadString) > UINT_MAX) {
                throw std::invalid_argument("num of words has to be 32 bit number");
            }
            address = std::stol(addressString);
            numOfWordsToRead = std::stol(numOfWordsToReadString);
            if (numOfWordsToRead < 1) {
                throw std::invalid_argument("num of words has to be greater than 1");
            }
            command = std::shared_ptr<ProgramCommand>(new ReadSilentCommand(address, numOfWordsToRead));
        } else {
            HexArgumentReader hexArgumentReader;
            address = hexArgumentReader.readWord(addressString);
            numOfWordsToRead = hexArgumentReader.readWord(numOfWordsToReadString);
            if (numOfWordsToRead < 1) {
                throw std::invalid_argument("num of words has to be greater than 1");
            }
            command = std::shared_ptr<ProgramCommand>(new ReadVerboseCommand(address, numOfWordsToRead));
        }
        return command;
    }
};


#endif //BRAM_CONTROLLER_PROJECT_READ_COMMAND_FACTORY_HPP
