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
           "\tSIZE (num of bytes), how big block to read should be\n\n"
           "-w VALUE [OFFSET] write to memory\n"
           "\tVALUE in hex to put in memory\n"
           "\tOFFSET address relative to BRAM staring position, where value will be set. Smallest block is byte.\n\n"
           "-c clears BRAM\n\n"
           "Examples of use:\n"
           "-receive data, no offset, 24 bytes block data: ./bram -r 0 24\n"
           "-writes bytes into memory: ./bram -w 0x50 1020\n"
           "-clear BRAM and read config from different file: ./bram bram-test.conf -c\n",
           program_name);
}

//---> read
void read_from_bram(long start_address, long max_address, long offset_bytes, long word_size);
void write_to_bram(long start_address, long max_address, char *bytes, long bytes_size, long offset);
void clear_bram(long start_address, long max_address);
//---> write
