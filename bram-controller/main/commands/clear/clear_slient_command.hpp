//
// Created by andrzej on 20.06.19.
//

#ifndef FPGA_SLOW_CONTROL_CLEAR_SLIENT_COMMAND_HPP
#define FPGA_SLOW_CONTROL_CLEAR_SLIENT_COMMAND_HPP


class ClearSilentCommand : public ClearCommand {
public:
    ClearSilentCommand(uint address, uint numOfWordsToClear): ClearCommand(address, numOfWordsToClear) {}
};

#endif //FPGA_SLOW_CONTROL_CLEAR_SLIENT_COMMAND_HPP
