//
// Created by mijo on 7/21/19.
//

#ifndef BRAM_CONTROLLER_PROJECT_CONFIGURATION_LOADER_H
#define BRAM_CONTROLLER_PROJECT_CONFIGURATION_LOADER_H


#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <stdexcept>
//#include <iostream>
#include <fstream>
#include <vector>
#include "hex_argument_reader.hpp"

class ConfigurationLoader {
private:
public:
    std::ifstream file;
    const char argumentDelimiter = '=';
    const char listDelimiter = ',';

    explicit ConfigurationLoader(std::string const &fileLocation) {
        file = std::ifstream(fileLocation.c_str());
        if (!file) {
            throw std::invalid_argument("cannot open configuration file");
        }
    }

    bool getAsBool(std::string const &argumentName) {
        const std::string value = getAsString(argumentName);
        if (value == "0" || value == "FALSE" || value == "false") {
            return false;
        }
        if (value == "1" || value == "TRUE" || value == "true") {
            return true;
        }
        throw std::invalid_argument("cannot parse argument to boolean!");
    }

    int getAsInt(std::string const &argumentName) {
        const std::string value = getAsString(argumentName);
        return std::stoi(value);
    }

    uint getAsUInt(std::string const &argumentName) {
        const std::string value = getAsString(argumentName);
        return std::stol(value);
    }

    long getAsLong(std::string const &argumentName) {
        const std::string value = getAsString(argumentName);
        return std::stol(value);
    }

    ulong getAsULong(std::string const &argumentName) {
        const std::string value = getAsString(argumentName);
        return std::stoul(value);
    }

    std::vector<uint> getAsWordList(std::string const &argumentName) {
        std::string list = getAsString(argumentName);
        if (list.empty()) {
            throw std::invalid_argument("cannot find argument in file!");
        }
        std::vector<std::string> stringValues = split(list, listDelimiter);
        std::vector<uint> values;
        HexArgumentReader hexArgumentReader;
        for (const auto & stringValue : stringValues) {
            uint word = hexArgumentReader.readWord(stringValue);
            values.push_back(word);
        }
        return values;
    }

    uint getAsWord(std::string const &argumentName) {
        const std::string value = getAsString(argumentName);
        HexArgumentReader hexArgumentReader;
        return hexArgumentReader.readWord(value);
    }

    std::string getAsString(std::string const &argumentName) {
        std::string line;
        while (getline(file, line)) {
            if (line.find(argumentName, 0) == 0 && line.find(argumentDelimiter) != std::string::npos) {
                line = split(line, argumentDelimiter)[1];
                break;
            }
        }
        file.clear();
        file.seekg(0, std::ifstream::beg);
        if (line.empty()) {
            throw std::invalid_argument("cannot get argument! " + argumentName);
        }
        return line;
    }

    ~ConfigurationLoader() {
        if (file) {
            file.close();
        }
    }

private:
    std::vector<std::string> split(std::string & value, char delimiter) {
        size_t position = 0;
        std::string token;
        std::vector<std::string> values;
        while ((position = value.find(delimiter)) != std::string::npos) {
            token = value.substr(0, position);
            values.push_back(token);
            value.erase(0, value.find(delimiter) + 1); // +1 -> delimiter.length()
        }
        values.push_back(value);
        return values;
    }
};


#endif //BRAM_CONTROLLER_PROJECT_CONFIGURATION_LOADER_H
