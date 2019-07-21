//
// Created by mijo on 7/21/19.
//

#include <cstdio>
#include <stdexcept>

int main(int argc, char *argv[]) {
    printf("Herro mister\n");
    if (argc < 2) {
        throw std::invalid_argument("configuration file not provided!");
    }
    return 0;
}