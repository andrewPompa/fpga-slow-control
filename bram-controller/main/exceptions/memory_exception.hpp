//
// Created by andrzej on 23.06.19.
//

#ifndef BRAM_CONTROLLER_PROJECT_MEMORY_EXCEPTION_HPP
#define BRAM_CONTROLLER_PROJECT_MEMORY_EXCEPTION_HPP


#include <exception>
#include <string>


class MemoryException : public std::exception {
private:
    const std::string & message;
public:
    MemoryException(const std::string & message): message(message) {}

    const char * what () const noexcept override {
        return message.c_str();
    }
};


#endif //BRAM_CONTROLLER_PROJECT_MEMORY_EXCEPTION_HPP
