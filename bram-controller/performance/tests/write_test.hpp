//
// Created by andrzej on 25.07.19.
//

#ifndef BRAM_CONTROLLER_PROJECT_WRITE_TEST_HPP
#define BRAM_CONTROLLER_PROJECT_WRITE_TEST_HPP


#include <commands/write/write_silent_command.hpp>
#include <commands/read/read_silent_command.hpp>
#include <chrono>
#include <random>
#include "../test_statistics.hpp"

class WriteTest {
public:
    void performTest(uint address, ulong numOfTest, ulong testSize, bool saveResults, uint saveAddress, int counter) {
        printf("Running %ld tests with %ld words for 0x%X\n", numOfTest, testSize, address);
        auto *writes = new double[numOfTest];
        for (int i = 0; i < numOfTest; ++i) {
            std::shared_ptr<uint> testWords = generateRandomWords(testSize);
            WriteSilentCommand writeSilentCommand(address, testSize, testWords);

            auto startWrite = std::chrono::high_resolution_clock::now();
            writeSilentCommand.execute();
            auto finishWrite = std::chrono::high_resolution_clock::now();

            writes[i] = (finishWrite - startWrite).count();

            if (saveResults && (i + 1) % 1000 == 0) {
                TestStatistics writeStatistics(writes, i, testSize);
                writeStatistics.calculate();
                std::shared_ptr<uint> speed(new uint[1]);
                speed.get()[0] = writeStatistics.speed * 5000;
                WriteSilentCommand writeSpeedCommand(saveAddress + (counter * 4), 1, speed);
                writeSpeedCommand.execute();
            }
        }
        TestStatistics writeStatistics(writes, numOfTest, testSize);
        writeStatistics.calculate();
        printf("write statistics: ");
        writeStatistics.print();

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


#endif //BRAM_CONTROLLER_PROJECT_WRITE_TEST_HPP
