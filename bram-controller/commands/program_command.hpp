//
// Created by andrzej on 16.06.19.
//

#ifndef BRAM_CONTROLLER_PROGRAM_COMMAND_HPP
#define BRAM_CONTROLLER_PROGRAM_COMMAND_HPP


class ProgramCommand {
public:
    virtual int execute() = 0;
};


#endif //BRAM_CONTROLLER_PROGRAM_COMMAND_HPP
