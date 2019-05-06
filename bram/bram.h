#ifndef FPGA_SLOW_CONTROL_BRAM_H
#define FPGA_SLOW_CONTROL_BRAM_H

#endif //FPGA_SLOW_CONTROL_BRAM_H


void print_help(char* program_name) {
    printf("Program to manage BRAM memory block. Usage:\n"
           "%s [bram.conf] --MODE\n"
           "[bram.conf] config file location, if location will not be provided, program will search file in current location\n"
           "--------------- MODES ---------------\n"
           "-r [OFFSET] [SIZE] read memory block, if none of additional options will be provided, all BRAM block will be printed\n"
           "-w VALUE [OFFSET] [SIZE] write to memory block, if only VALUE will be set, value will be write to all BRAM block\n"
           "\twhen OFFSET is also set, value will be write from that offset to end BRAM block\n"
           "\twhen SIZE is set, only that memory block will be changed. If SIZE is bigger than VALUE, error will be thrown\n"
           "-c clears BRAM\n",
           program_name);
}

//---> read
void read();
//---> write
