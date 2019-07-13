//
// Created by andrzej on 11.07.19.
//

#ifndef BRAM_CONTROLLER_PROJECT_HEX_ARGUMENT_READER_HPP
#define BRAM_CONTROLLER_PROJECT_HEX_ARGUMENT_READER_HPP

#include <string>
#include <regex>

const std::regex hexWordRegex("0x[0-9a-fA-F]{1,8}");
const std::regex hexWordsRegex("0x([0-9a-fA-F]{8})*[0-9a-fA-F]{1,8}");

class HexArgumentReader {
public:
    uint readWord(const std::string& stringValue) {
		if (!std::regex_match(stringValue, hexWordRegex)) {
            throw std::invalid_argument("invalid hex value! " + stringValue);
		}
		return std::stol(stringValue, nullptr, 16);
	}

	std::shared_ptr<uint> readWords(std::string& stringValue, uint numOfWords) {
        if (!std::regex_match(stringValue, hexWordsRegex)) {
            throw std::invalid_argument("invalid hex value! " + stringValue);
        }
        stringValue = stringValue.erase(0, 2);

        std::shared_ptr<uint> valueToWrite(new uint[numOfWords]);
        if (stringValue.size() < 8) {
            valueToWrite.get()[0] = std::stol(stringValue, nullptr, 16);
            return valueToWrite;
        }
        for (int i = 0; i < numOfWords; ++i) {
            valueToWrite.get()[i] = std::stoll(stringValue.substr(i * 8, 8), nullptr, 16);
        }
        return valueToWrite;
    }

};


#endif //BRAM_CONTROLLER_PROJECT_HEX_ARGUMENT_READER_HPP
