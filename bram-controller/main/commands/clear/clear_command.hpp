//
// Created by andrzej on 22.06.19.
//

#ifndef BRAM_CONTROLLER_PROJECT_CLEAR_COMMAND_HPP
#define BRAM_CONTROLLER_PROJECT_CLEAR_COMMAND_HPP



class ClearCommand : public ProgramCommand {
private:
    uint address;
    uint numOfWordsToClear;
public:
    ClearCommand(uint address, uint numOfWordsToClear): address(address), numOfWordsToClear(numOfWordsToClear) {}

    int execute() override {
        return 0;
    }
};


#endif //BRAM_CONTROLLER_PROJECT_CLEAR_COMMAND_HPP
