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
#include <commands/write/write_program_memory_command.hpp>
#include <commands/read/read_program_memory_command.hpp>
#include "test_configuration.h"
#include "test_statistics.hpp"
#include "tests/processor_write_test.hpp"
#include "tests/processor_read_test.hpp"
#include "tests/processor_read_write_test.hpp"
#include "tests/write_test.hpp"
#include "tests/read_test.hpp"
#include "tests/read_write_test.hpp"

TestConfiguration parseArguments(std::string const &fileName) {
    ConfigurationLoader configurationLoader(fileName);
    TestConfiguration testConfiguration;
    testConfiguration.testMode = configurationLoader.getAsInt("test.mode");
    testConfiguration.runBigTest = configurationLoader.getAsBool("run.big.test");
    testConfiguration.addresses = configurationLoader.getAsWordList("addresses");
    testConfiguration.numOfTests = configurationLoader.getAsULong("num.of.tests");
    testConfiguration.smallTestSize = configurationLoader.getAsULong("words.small.test");
    testConfiguration.bigTestSize = configurationLoader.getAsULong("words.big.test");
    testConfiguration.bigTestSize = configurationLoader.getAsULong("words.big.test");
    testConfiguration.saveResults = configurationLoader.getAsBool("save.in.ram");
    testConfiguration.saveResultsAddress = configurationLoader.getAsWord("save.location");

    return testConfiguration;
}

void performProcessorTest(int mode, ulong numOfTest, ulong testSize, bool saveResults, uint saveAddress, int counter) {
    if (mode == 1) {
        ProcessorWriteTest writeTest;
        writeTest.performTest(numOfTest, testSize, saveResults, saveAddress, counter);
    } else if (mode == 2) {
        ProcessorReadTest readTest;
        readTest.performTest(numOfTest, testSize, saveResults, saveAddress, counter);
    } else if (mode == 3) {
        ProcessorReadWriteTest readWriteTest;
        readWriteTest.performTest(numOfTest, testSize, saveResults, saveAddress, counter);
    }
}

void performTest(int mode, uint address, ulong numOfTest, ulong testSize, bool saveResults, uint saveAddress, int counter) {
    if (mode == 1) {
        WriteTest writeTest;
        writeTest.performTest(address, numOfTest, testSize, saveResults, saveAddress, counter);
    } else if (mode == 2) {
        ReadTest readTest;
        readTest.performTest(address, numOfTest, testSize, saveResults, saveAddress, counter);
    } else if (mode == 3) {
        ReadWriteTest readWriteTest;
        readWriteTest.performTest(address, numOfTest, testSize, saveResults, saveAddress, counter);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("configuration file path not provided!\n");
        exit(EXIT_FAILURE);
    }
    TestConfiguration testConfiguration;
    try {
        testConfiguration = parseArguments(argv[1]);
        printf("Small test for %ld words\n", testConfiguration.smallTestSize);

        performProcessorTest(testConfiguration.testMode, testConfiguration.numOfTests, testConfiguration.smallTestSize, testConfiguration.saveResults, testConfiguration.saveResultsAddress, 0);
        for (int i = 0; i < testConfiguration.addresses.size(); ++i) {
            uint address = testConfiguration.addresses[i];
            performTest(testConfiguration.testMode, address, testConfiguration.numOfTests, testConfiguration.smallTestSize, testConfiguration.saveResults, testConfiguration.saveResultsAddress, i + 1);
        }

        if (!testConfiguration.runBigTest) {
            printf("Big test is disabled, skipping\n");
            return 0;
        }
        printf("Big test for %ld words\n", testConfiguration.bigTestSize);
        performProcessorTest(testConfiguration.testMode, testConfiguration.numOfTests, testConfiguration.bigTestSize, testConfiguration.saveResults, testConfiguration.saveResultsAddress, 0);
        for (int i = 0; i < testConfiguration.addresses.size(); ++i) {
            uint address = testConfiguration.addresses[i];
            performTest(testConfiguration.testMode, address, testConfiguration.numOfTests, testConfiguration.bigTestSize, testConfiguration.saveResults, testConfiguration.saveResultsAddress, i + 1);
        }
    } catch (std::invalid_argument const &e) {
        printf("error during getting configuration file: %s!\n", e.what());
        exit(EXIT_FAILURE);
    }
    return 0;
}