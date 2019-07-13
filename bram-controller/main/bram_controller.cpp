#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include "commands/command_factory.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    vector<string>* args = new vector<string>(argv, argv + argc);
    vector<string> v;
    CommandFactory commandFactory(args);
    ProgramCommand *programCommand = commandFactory.create();
    if (programCommand != nullptr) {
        programCommand->execute();
    }
}