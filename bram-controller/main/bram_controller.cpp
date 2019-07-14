#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include "commands/command_factory.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    vector<string> args(argv, argv + argc);
    CommandFactory commandFactory(args);
    std::shared_ptr<ProgramCommand> programCommand = commandFactory.create();
    if (programCommand != nullptr) {
        programCommand->execute();
    }
}