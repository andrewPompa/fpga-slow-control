//
// Created by andrzej on 20.06.19.
//

#ifndef FPGA_SLOW_CONTROL_CLEAR_VERBOSE_COMMAND_HPP
#define FPGA_SLOW_CONTROL_CLEAR_VERBOSE_COMMAND_HPP


class ClearVerboseCommand : public ClearCommand {
public:
    ClearVerboseCommand(uint address, uint numOfWordsToClear): ClearCommand(address, numOfWordsToClear) {}

    int execute() override {
        uint* memory;
        try {
            memory = openMemory(address, numOfWordsToClear);
        } catch (const MemoryException & e) {
            printf("exception occur during opening memory block: %s\n",e.what());
            return 1;
        }
        for (int i = 0; i < numOfWordsToClear; ++i) {
            memory[i] = 0;
        }
        printf("cleared %u words, starting from address: %u\n", address, numOfWordsToClear);
        return 0;
    }
};


#endif //FPGA_SLOW_CONTROL_CLEAR_VERBOSE_COMMAND_HPP
