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
        printf("min: %.1f[ns], max: %.1f[ns], mean %.1f[ns], median %.1f[ns], deviation: %.1f[ns]\n", min, max, mean, median, standardDeviation);
        printHistogram();
    }

private:
    void printHistogram() {
        double k = std::sqrt(testSize);
        double h = (max - min) / k;
        uint histogram[static_cast<int>(k)];
        int i;
        for (i = 0; i < k; ++i) {
            histogram[i] = 0;
        }
        for (i = 0; i < testSize; ++i) {
            int n = (double (times[i] - min)) / h;
            histogram[n]++;
        }
        uint maxHistogram = 0;
        for (i = 0; i < k; ++i) {
            if (histogram[i] >= maxHistogram) {
                maxHistogram = histogram[i];
            }
        }
        for (i = 0; i < k; ++i) {
            if (150 * histogram[i] / maxHistogram < 1) {
                continue;
            }
            printf("[%03d] = (%.0f[ns]  - %.0f[ns]) %04d values\t", i, min + i * k, min + (i + 1) * k, histogram[i]);
            for (int j = 0; j < 150 * histogram[i] / maxHistogram; ++j) {
                printf("*");
            }
            printf("\n");

        }
    }
};


#endif //BRAM_CONTROLLER_PROJECT_TEST_STATISTICS_HPP
