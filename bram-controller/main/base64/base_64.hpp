//
// Created by andrzej on 25.06.19.
//

#ifndef BRAM_CONTROLLER_PROJECT_BASE_64_HPP
#define BRAM_CONTROLLER_PROJECT_BASE_64_HPP

#include <vector>
#include <string>
#include <memory>

class Base64 {
public:
    std::string encode(u_char *buffer, uint bufferLength);
    std::shared_ptr<uint> decodeWords(std::string const &encoded);
};


#endif //BRAM_CONTROLLER_PROJECT_BASE_64_HPP
