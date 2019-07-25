//
// Created by andrzej on 25.07.19.
//

#ifndef BRAM_CONTROLLER_PROJECT_READ_TEST_HPP
#define BRAM_CONTROLLER_PROJECT_READ_TEST_HPP


#include <commands/write/write_silent_command.hpp>
#include <commands/read/read_silent_command.hpp>
#include <chrono>
#include <commands/read/performance_check_read_command.hpp>
#include "../test_statistics.hpp"

class ReadTest {
public:
    void performTest(uint address, ulong numOfTest, ulong testSize) {
        printf("Running %ld tests with %ld words for 0x%X\n", numOfTest, testSize, address);
        auto *reads = new double[numOfTest];
        for (int i = 0; i < numOfTest; ++i) {
            PerformanceCheckReadCommand readCommand(address, testSize);
            auto startRead = std::chrono::high_resolution_clock::now();
            readCommand .execute();
            auto finishRead = std::chrono::high_resolution_clock::now();

            reads[i] = (finishRead - startRead).count();
        }
        TestStatistics readStatistics(reads, numOfTest, testSize);
        readStatistics.calculate();
        printf("read statistics: ");
        readStatistics.print();

        delete[] reads;
    }
};


#endif //BRAM_CONTROLLER_PROJECT_READ_TEST_HPP
