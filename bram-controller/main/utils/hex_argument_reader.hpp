//
// Created by andrzej on 11.07.19.
//

#ifndef BRAM_CONTROLLER_PROJECT_HEX_ARGUMENT_READER_HPP
#define BRAM_CONTROLLER_PROJECT_HEX_ARGUMENT_READER_HPP

#include <string>
#include <regex>

const std::regex hexWordRegex("0x[0-9a-fA-F]{1,8}");

class HexArgumentReader {
public:
    uint readWord(const std::string& stringValue) {
		if (!std::regex_match(stringValue, hexWordRegex)) {
            throw std::invalid_argument("invalid hex value! " + stringValue);
		}
		return std::stol(stringValue, nullptr, 16);
	}
};


#endif //BRAM_CONTROLLER_PROJECT_HEX_ARGUMENT_READER_HPP
