//
// Created by mijo on 7/21/19.
//

#include <cstdio>
#include <stdexcept>
#include <utils/configuration_loader.h>
#include "test_configuration.h"

TestConfiguration parseArguments(std::string const &fileName) {
    ConfigurationLoader configurationLoader(fileName);
    TestConfiguration testConfiguration;
    testConfiguration.addresses = configurationLoader.getAsWordList("addresses");
    testConfiguration.numOfTests = configurationLoader.getAsUInt("num.of.tests");
    testConfiguration.smallTestSize = configurationLoader.getAsUInt("words.small.test");
    testConfiguration.bigTestSize = configurationLoader.getAsUInt("words.big.test");
    return testConfiguration;
}


int main(int argc, char *argv[]) {
    printf("Herro mister\n");
    if (argc < 2) {
        printf("configuration file path not provided!\n");
        exit(EXIT_FAILURE);
    }
    TestConfiguration testConfiguration = parseArguments(argv[1]);
    return 0;
}