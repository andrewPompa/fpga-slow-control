#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define printf(...) \
 fprintf(stdout, __VA_ARGS__); \
 fflush(stdout);

typedef long long int u64;

const int execution_count = 500;
const int sleep_time_microseconds = 500000;

int main()
{
    printf("GPIO TEST...\n");

    unsigned int bram_size = 0xFA00;
    off_t bram_pbase = 0x41200000; // physical base address
    u64 *bram64_vptr;
    int fd;

    printf("try open memory...\n");
    if ((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) {
        printf("ERROR: cannot open GPIO block...\n");
        return 1;
    }
    printf("memory opened, start blinking\n");

    bram64_vptr = (u64 *)mmap(NULL, bram_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, bram_pbase);
    bram64_vptr[0] = 0x0;
    for (int i = 0; i < execution_count; ++i) {
        bram64_vptr[0] = 0x1;
        usleep(sleep_time_microseconds);
        bram64_vptr[0] = 0x0;
        usleep(sleep_time_microseconds);
    }
    close(fd);

    printf("End of test\n");
}