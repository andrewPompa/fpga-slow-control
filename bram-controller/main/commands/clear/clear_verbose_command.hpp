//
// Created by andrzej on 20.06.19.
//

#ifndef FPGA_SLOW_CONTROL_CLEAR_VERBOSE_COMMAND_HPP
#define FPGA_SLOW_CONTROL_CLEAR_VERBOSE_COMMAND_HPP


class ClearVerboseCommand : public ClearCommand {
public:
    ClearVerboseCommand(uint address, uint numOfWordsToClear): ClearCommand(address, numOfWordsToClear) {}

    int execute() override {
        return 0;
    }
};


#endif //FPGA_SLOW_CONTROL_CLEAR_VERBOSE_COMMAND_HPP
