//
// Created by andrzej on 20.06.19.
//

#ifndef FPGA_SLOW_CONTROL_CLEAR_SLIENT_COMMAND_HPP
#define FPGA_SLOW_CONTROL_CLEAR_SLIENT_COMMAND_HPP


class ClearSilentCommand : public ClearCommand {
public:
    ClearSilentCommand(uint address, uint numOfWordsToClear): ClearCommand(address, numOfWordsToClear) {}

    int execute() override {
        uint* memory;
        try {
            memory = openMemory(address, numOfWordsToClear);
        } catch (const MemoryException & e) {
            return 1;
        }
        for (int i = 0; i < numOfWordsToClear; ++i) {
            memory[i] = 0;
        }
        closeMemory(memory);
        return 0;
    }
};

#endif //FPGA_SLOW_CONTROL_CLEAR_SLIENT_COMMAND_HPP
