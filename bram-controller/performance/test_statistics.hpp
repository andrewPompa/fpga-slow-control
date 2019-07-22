//
// Created by andrzej on 21.07.19.
//

#ifndef BRAM_CONTROLLER_PROJECT_TEST_STATISTICS_HPP
#define BRAM_CONTROLLER_PROJECT_TEST_STATISTICS_HPP


class TestStatistics {
public:
    double mean = 0.0;
    double median = 0.0;
    double standardDeviation = 0.0;
    double min = 0.0;
    double max = 0.0;
private:
    double * times;
    ulong testSize;

public:
    explicit TestStatistics(double *times, ulong testSize): times(times), testSize(testSize) {}

    void calculate() {
        double sum = 0.0;
        double squareSum = 0.0;
        std::sort(times, times + testSize);
        for (int i = 0; i < testSize; ++i) {
            sum += times[i];
            squareSum += times[i] * times[i];
        }
        min = times[0];
        max = times[testSize - 1];
        mean = sum / testSize;
        median = times[testSize / 2];
        standardDeviation = std::sqrt(squareSum / testSize - mean * mean);
    }

    void print() {
        printf("min: %.0f, max: %.0f, mean %f, median %f, deviation: %f\n", min, max, mean, median, standardDeviation);
    }
};


#endif //BRAM_CONTROLLER_PROJECT_TEST_STATISTICS_HPP
