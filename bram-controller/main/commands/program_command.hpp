//
// Created by andrzej on 16.06.19.
//

#ifndef BRAM_CONTROLLER_PROGRAM_COMMAND_HPP
#define BRAM_CONTROLLER_PROGRAM_COMMAND_HPP


#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "../exceptions/memory_exception.hpp"
#include "../../program_settings.h"

class ProgramCommand {
public:
    virtual int execute() = 0;

protected:
    uint *openMemory(uint address, uint numOfWords) {
        if (address % 4 != 0) {
            throw MemoryException("address has to be divisible by 32 (word size)");
        }
        int fd = open(MEMORY_FILE_LOCATION, O_RDWR | O_SYNC);
        if (fd < 0) {
            throw MemoryException("cannot open memory block");
        }
        size_t bramSize = numOfWords * 4;
        size_t pageSize = sysconf(_SC_PAGE_SIZE);
        off_t startAddress = (address / pageSize) * pageSize;
        off_t pageOffset = address - startAddress;
        uint *memory = (uint *) mmap(nullptr, pageOffset + bramSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, startAddress);
        memory += pageOffset / 4;
        if (memory == MAP_FAILED) {
            close(fd);
            throw MemoryException("cannot map memory block");
        }
        return memory;
    }
};


#endif //BRAM_CONTROLLER_PROGRAM_COMMAND_HPP
