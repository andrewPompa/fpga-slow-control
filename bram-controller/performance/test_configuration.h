//
// Created by mijo on 7/21/19.
//

#ifndef BRAM_CONTROLLER_PROJECT_TEST_CONFIGURATION_H
#define BRAM_CONTROLLER_PROJECT_TEST_CONFIGURATION_H


class TestConfiguration {
public:
    bool runBigTest = false;
    ulong numOfTests = 100000;
    ulong smallTestSize = 1000 / 4;
    ulong bigTestSize = 1000000 / 4;
    std::vector<uint> addresses;
    int testMode;
    bool saveResults = false;
    uint saveResultsAddress = 0x0;
};


#endif //BRAM_CONTROLLER_PROJECT_TEST_CONFIGURATION_H
