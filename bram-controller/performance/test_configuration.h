//
// Created by mijo on 7/21/19.
//

#ifndef BRAM_CONTROLLER_PROJECT_TEST_CONFIGURATION_H
#define BRAM_CONTROLLER_PROJECT_TEST_CONFIGURATION_H


class TestConfiguration {
public:
    uint numOfTests = 100000;
    uint smallTestSize = 1000000 / 4;
    uint bigTestSize = 1000 / 4;
    std::vector<uint> addresses;
};


#endif //BRAM_CONTROLLER_PROJECT_TEST_CONFIGURATION_H
