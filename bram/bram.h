#ifndef FPGA_SLOW_CONTROL_BRAM_H
#define FPGA_SLOW_CONTROL_BRAM_H

#endif //FPGA_SLOW_CONTROL_BRAM_H


void read_from_bram(long start_address, long words);
void write_to_bram(long start_address, char *bytes, long words);
