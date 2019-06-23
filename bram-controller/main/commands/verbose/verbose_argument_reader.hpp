//
// Created by andrzej on 17.06.19.
//

#ifndef BRAM_CONTROLLER_PROJECT_VERBOSE_ARGUMENT_READER_HPP
#define BRAM_CONTROLLER_PROJECT_VERBOSE_ARGUMENT_READER_HPP


#include <string>

class VerboseArgumentReader {

    std::string s = "0xfffefffe";
    unsigned int x = std::stoul(s, nullptr, 16);
};


#endif //BRAM_CONTROLLER_PROJECT_VERBOSE_ARGUMENT_READER_HPP
