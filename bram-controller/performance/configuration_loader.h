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

class ConfigurationLoader {
private:
public:
    std::ifstream file;

    explicit ConfigurationLoader(std::string const &fileLocation) {
        file = std::ifstream(fileLocation.c_str());
        if (!file) {
            throw std::invalid_argument("cannot open configuration file");
        }
    }

    int getAsInt(std::string const &argumentName) {
        const std::string value = getAsString(argumentName);
        return 0;
    }
    std::string getAsString(std::string const &argumentName) {
        std::string line;
        while (getline(file, line)) {
            printf("line: %s\n", line.c_str());
        }
        file.clear();
        file.seekg(0, std::ifstream::beg);
        return "hey";
    }

    ~ConfigurationLoader() {
        printf("descruction\n");
        if (file) {
            file.close();
        }
    }
};


#endif //BRAM_CONTROLLER_PROJECT_CONFIGURATION_LOADER_H
