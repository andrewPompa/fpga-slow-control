//
// Created by andrzej on 21.07.19.
//

#ifndef BRAM_CONTROLLER_PROJECT_TEST_STATISTICS_HPP
#define BRAM_CONTROLLER_PROJECT_TEST_STATISTICS_HPP


class TestStatistics {
public:
    double mean = 0.0;
    double median = 0.0;
    double mode = 0.0;
    double standardDeviation = 0.0;

    void print() {
        printf("mean %f, median %f, mode: %f, deviation: %f\n", mean, median, mode, standardDeviation);
    }
};


#endif //BRAM_CONTROLLER_PROJECT_TEST_STATISTICS_HPP
