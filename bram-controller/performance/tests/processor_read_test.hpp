//
// Created by andrzej on 25.07.19.
//

#ifndef BRAM_CONTROLLER_PROJECT_PROCESSOR_READ_TEST_HPP
#define BRAM_CONTROLLER_PROJECT_PROCESSOR_READ_TEST_HPP


#include <commands/write/write_silent_command.hpp>
#include <commands/read/read_silent_command.hpp>
#include <chrono>
#include <commands/read/read_program_memory_command.hpp>
#include "../test_statistics.hpp"

class ProcessorReadTest {
public:
    void performTest(ulong numOfTest, ulong testSize) {
        printf("[PROCESSOR] Running %ld tests with %ld words\n", numOfTest, testSize);
        auto *reads = new double[numOfTest];
        auto *programMemoryBlock = new uint[testSize];
        for (int i = 0; i < numOfTest; ++i) {
            ReadProgramMemoryCommand readProgramMemoryCommand(programMemoryBlock, testSize);
            auto startRead = std::chrono::high_resolution_clock::now();
            readProgramMemoryCommand.execute();
            auto finishRead = std::chrono::high_resolution_clock::now();

            reads[i] = (finishRead - startRead).count();
        }
        TestStatistics readStatistics(reads, numOfTest, testSize);
        readStatistics.calculate();
        printf("[PROCESSOR] read statistics: ");
        readStatistics.print();

        delete[] programMemoryBlock;
        delete[] reads;
    }
};


#endif //BRAM_CONTROLLER_PROJECT_PROCESSOR_READ_TEST_HPP
