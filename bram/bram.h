#ifndef FPGA_SLOW_CONTROL_BRAM_H
#define FPGA_SLOW_CONTROL_BRAM_H

#endif //FPGA_SLOW_CONTROL_BRAM_H


void print_help(char* program_name) {
    printf("Program to manage BRAM memory block. Usage:\n"
           "%s [bram.conf] --MODE\n"
           "[bram.conf] config file location, if location will not be provided, program will search file in current location\n"
           "--------------- MODES ---------------\n"
           "-r [OFFSET] [SIZE] read memory block, if none of additional options will be provided, all BRAM block will be printed\n"
           "\tOFFSET (num of bytes from starting address), starting position to read the data\n"
           "\tSIZE (num of bytes from starting address), how big block to read should be\n"
           "-w VALUE [OFFSET] write to memory\n"
           "\tVALUE value to put in memory, max value: 0xFFFFFFFF (4 bytes)\n"
           "\tOFFSET address relative to BRAM staring position, where value will be set. Smallest block is byte.\n"
           "-c clears BRAM\n",
           program_name);
//    "\twhen SIZE is set, only that memory block will be changed. If SIZE is bigger than VALUE, error will be thrown\n"
}

//---> read
void read_from_bram(long start_address, long max_address, long offset_bytes, long word_size);
void write_to_bram(long start_address, long max_address, char *bytes, long offset);
//---> write
