//
// Created by mijo on 7/21/19.
//

#include <cstdio>
#include <stdexcept>
#include <utils/configuration_loader.h>
#include <chrono>
#include <commands/write/write_silent_command.hpp>
#include <commands/read/read_silent_command.hpp>
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

}

TestStatistics calculateStatistics(double *results, ulong numOfTests) {
    return TestStatistics();
}

void performTest(uint address, ulong numOfTest, ulong testSize) {
    printf("Running %ld tests with %ld words for 0x%x\n", numOfTest, testSize, address);
    double reads[numOfTest];
    double writes[numOfTest];
    double readsAndWrites[numOfTest];
    for (int i = 0; i < numOfTest; ++i) {
        std::shared_ptr<uint> testWords = generateRandomWords(testSize);
        WriteSilentCommand writeSilentCommand(address, testSize, testWords);
        ReadSilentCommand readSilentCommand(address, testSize);

        auto startWrite = std::chrono::high_resolution_clock::now();
        writeSilentCommand.execute();
        auto finishWriteStartRead = std::chrono::high_resolution_clock::now();
        std::string readValue = readSilentCommand.readValue();
        auto finishRead = std::chrono::high_resolution_clock::now();
        //todo: compare values
        writes[i] = (finishWriteStartRead - startWrite).count();
        reads[i] = (finishRead - finishWriteStartRead).count();
        readsAndWrites[i] = (finishRead - startWrite).count();
    }
    auto writeStatistics = calculateStatistics(writes, numOfTest);
    auto readStatistics = calculateStatistics(reads, numOfTest);
    auto readAndWriteStatistics = calculateStatistics(readsAndWrites, numOfTest);

    writeStatistics.print();
    readStatistics.print();
    readAndWriteStatistics.print();
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
    } catch (std::invalid_argument const &e) {
        printf("error during getting configuration file: %s!\n", e.what());
        exit(EXIT_FAILURE);
    }
    for (uint address : testConfiguration.addresses) {
        performTest(address, testConfiguration.numOfTests, testConfiguration.smallTestSize);
    }
    return 0;
}