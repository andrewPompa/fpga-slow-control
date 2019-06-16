#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include "commands/command_factory.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    vector<string> args(argv, argv + argc);
    printf("pyy: %d\n", args.size());
    for (string i : args) {
        cout << i << endl;
        printf("test: %s\n", i.c_str());
    }
    CommandFactory commandFactory(argc, argv);
    ProgramCommand *command = commandFactory.create();
    if (command != nullptr) {
        command->execute();
    }
}