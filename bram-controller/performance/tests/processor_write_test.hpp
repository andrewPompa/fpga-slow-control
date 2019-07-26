//
// Created by andrzej on 25.07.19.
//

#ifndef BRAM_CONTROLLER_PROJECT_PROCESSOR_WRITE_TEST_HPP
#define BRAM_CONTROLLER_PROJECT_PROCESSOR_WRITE_TEST_HPP


#include <commands/write/write_silent_command.hpp>
#include <chrono>
#include <random>
#include <commands/write/write_program_memory_command.hpp>
#include "../test_statistics.hpp"

class ProcessorWriteTest {
public:
    void performTest(ulong numOfTest, ulong testSize) {
        printf("[PROCESSOR] Running %ld tests with %ld words\n", numOfTest, testSize);

        auto *writes = new double[numOfTest];
        auto *programMemoryBlock = new uint[testSize];
        for (int i = 0; i < numOfTest; ++i) {
            std::shared_ptr<uint> testWords = generateRandomWords(testSize);
            WriteProgramMemoryCommand writeProgramMemoryCommand(programMemoryBlock, testSize, testWords);

            auto startWrite = std::chrono::high_resolution_clock::now();
            writeProgramMemoryCommand.execute();
            auto finishWrite = std::chrono::high_resolution_clock::now();

            writes[i] = (finishWrite - startWrite).count();
        }
        TestStatistics writeStatistics(writes, numOfTest, testSize);
        writeStatistics.calculate();
        printf("[PROCESSOR] write statistics: ");
        writeStatistics.print();

        delete[] programMemoryBlock;
        delete[] writes;
    }

private:
    std::shared_ptr<uint> generateRandomWords(ulong testSize) {
        std::shared_ptr<uint> value(new uint[testSize]);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<uint> dis(1, UINT32_MAX);

        for (int n = 0; n < testSize; ++n) {
            value.get()[n] = dis(gen);
        }
        return value;
    }
};


#endif //BRAM_CONTROLLER_PROJECT_PROCESSOR_WRITE_TEST_HPP
