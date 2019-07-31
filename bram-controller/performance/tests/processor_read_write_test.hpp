//
// Created by andrzej on 25.07.19.
//

#ifndef BRAM_CONTROLLER_PROJECT_PROCESSOR_READ_WRITE_TEST_HPP
#define BRAM_CONTROLLER_PROJECT_PROCESSOR_READ_WRITE_TEST_HPP


#include <commands/write/write_silent_command.hpp>
#include <commands/read/read_silent_command.hpp>
#include <chrono>
#include <random>
#include <commands/write/write_program_memory_command.hpp>
#include <commands/read/read_program_memory_command.hpp>
#include "../test_statistics.hpp"

class ProcessorReadWriteTest {
public:
    void performTest(ulong numOfTest, ulong testSize, bool saveResults, uint saveAddress, int counter) {
        printf("[PROCESSOR] Running %ld tests with %ld words\n", numOfTest, testSize);
        auto *readsAndWrites = new double[numOfTest];
        auto *programMemoryBlock = new uint[testSize];
        for (int i = 0; i < numOfTest; ++i) {
            std::shared_ptr<uint> testWords = generateRandomWords(testSize);
            WriteProgramMemoryCommand writeProgramMemoryCommand(programMemoryBlock, testSize, testWords);
            ReadProgramMemoryCommand readProgramMemoryCommand(programMemoryBlock, testSize);

            auto startWrite = std::chrono::high_resolution_clock::now();
            writeProgramMemoryCommand.execute();
            auto finishWriteStartRead = std::chrono::high_resolution_clock::now();
            readProgramMemoryCommand.execute();
            auto finishRead = std::chrono::high_resolution_clock::now();

            readsAndWrites[i] = (finishRead - startWrite).count();

            if (saveResults && (i + 1) % 1000 == 0) {
                TestStatistics readsAndWritesStatistics(readsAndWrites, i, testSize);
                readsAndWritesStatistics.calculate();
                std::shared_ptr<uint> speed(new uint[1]);
                speed.get()[0] = readsAndWritesStatistics.speed * 5000;
                WriteSilentCommand writeSpeedCommand(saveAddress + (counter * 4), 1, speed);
                writeSpeedCommand.execute();
            }
        }

        TestStatistics readAndWriteStatistics(readsAndWrites, numOfTest, testSize);
        readAndWriteStatistics.calculate();
        printf("[PROCESSOR] read and write statistics: ");
        readAndWriteStatistics.print();

        delete[] programMemoryBlock;
        delete[] readsAndWrites;
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


#endif //BRAM_CONTROLLER_PROJECT_READ_WRITE_TEST_HPP
