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
    void performTest(ulong numOfTest, ulong testSize, bool saveResults, uint saveAddress, int counter) {
        printf("[PROCESSOR] Running %ld tests with %ld words\n", numOfTest, testSize);
        auto *reads = new double[numOfTest];
        auto *programMemoryBlock = new uint[testSize];
        for (int i = 0; i < numOfTest; ++i) {
            ReadProgramMemoryCommand readProgramMemoryCommand(programMemoryBlock, testSize);
            auto startRead = std::chrono::high_resolution_clock::now();
            readProgramMemoryCommand.execute();
            auto finishRead = std::chrono::high_resolution_clock::now();

            reads[i] = (finishRead - startRead).count();

            if (saveResults && (i + 1) % 1000 == 0) {
                TestStatistics readStatistics(reads, i, testSize);
                readStatistics.calculate();
                std::shared_ptr<uint> speed(new uint[1]);
                speed.get()[0] = readStatistics.speed * 5000;
                WriteSilentCommand writeSpeedCommand(saveAddress + (counter * 4), 1, speed);
                writeSpeedCommand.execute();
            }
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
