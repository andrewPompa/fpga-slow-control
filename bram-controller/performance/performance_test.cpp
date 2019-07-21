#include <memory>

//
// Created by mijo on 7/21/19.
//

#include <cstdio>
#include <stdexcept>
#include <utils/configuration_loader.h>
#include <chrono>
#include <commands/write/write_silent_command.hpp>
#include <commands/read/read_silent_command.hpp>
#include <random>
#include "test_configuration.h"
#include "test_statistics.hpp"

TestConfiguration parseArguments(std::string const &fileName) {
    ConfigurationLoader configurationLoader(fileName);
    TestConfiguration testConfiguration;
    testConfiguration.addresses = configurationLoader.getAsWordList("addresses");
    testConfiguration.numOfTests = configurationLoader.getAsULong("num.of.tests");
    testConfiguration.smallTestSize = configurationLoader.getAsULong("words.small.test");
    testConfiguration.bigTestSize = configurationLoader.getAsULong("words.big.test");
    return testConfiguration;
}

std::shared_ptr<uint> generateRandomWords(ulong testSize) {
    auto value = std::make_shared<uint>(testSize);
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<uint> dist(1, 10);

    for (int i = 0; i < testSize; ++i) {
        value.get()[i] = dist(mt);
    }
    return value;
}

bool testIfOperationIsOk(std:: string const & readValue, std::shared_ptr<uint>& testWords, uint testSize) {
    Base64 base64;
    std::shared_ptr<uint> readWords = base64.decodeWords(readValue);
    for (int i = 0; i < testSize; ++i) {
        if (testWords.get()[i] != readWords.get()[i]) {
            return false;
        }
    }
    return true;
}

TestStatistics calculateStatistics(double *results, ulong numOfTests) {
    for (int i = 0; i < numOfTests; ++i) {
        printf("value[%d] = %f\n", i, results[i]);
    }
    return TestStatistics();
}

void performTest(uint address, ulong numOfTest, ulong testSize) {
    printf("Running %ld tests with %ld words for 0x%x\n", numOfTest, testSize, address);
    double reads[numOfTest];
    double writes[numOfTest];
    double readsAndWrites[numOfTest];
    for (int i = 0; i < numOfTest; ++i) {
        std::shared_ptr<uint> testWords = generateRandomWords(testSize);
//        WriteSilentCommand writeSilentCommand(address, testSize, testWords);
//        ReadSilentCommand readSilentCommand(address, testSize);

//        auto startWrite = std::chrono::high_resolution_clock::now();
//        writeSilentCommand.execute();
//        auto finishWriteStartRead = std::chrono::high_resolution_clock::now();
//        std::string readValue = readSilentCommand.readValue();
//        auto finishRead = std::chrono::high_resolution_clock::now();

//        if (!testIfOperationIsOk(readValue, testWords, testSize)) {
//            throw std::invalid_argument("read value is different than generated!");
//        }

//        writes[i] = (finishWriteStartRead - startWrite).count();
//        reads[i] = (finishRead - finishWriteStartRead).count();
//        readsAndWrites[i] = (finishRead - startWrite).count();
    }
//    auto writeStatistics = calculateStatistics(writes, numOfTest);
//    auto readStatistics = calculateStatistics(reads, numOfTest);
//    auto readAndWriteStatistics = calculateStatistics(readsAndWrites, numOfTest);
//
//    writeStatistics.print();
//    readStatistics.print();
//    readAndWriteStatistics.print();
}


int main(int argc, char *argv[]) {
    printf("Herro mister\n");
    if (argc < 2) {
        printf("configuration file path not provided!\n");
        exit(EXIT_FAILURE);
    }
    TestConfiguration testConfiguration;
    try {
        testConfiguration = parseArguments(argv[1]);
        for (uint address : testConfiguration.addresses) {
            performTest(address, testConfiguration.numOfTests, testConfiguration.smallTestSize);
        }
    } catch (std::invalid_argument const &e) {
        printf("error during getting configuration file: %s!\n", e.what());
        exit(EXIT_FAILURE);
    }
    return 0;
}