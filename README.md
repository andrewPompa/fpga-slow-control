### Pliki projektu
- Skrypty (katalog `scripts`)

`zrecv.sh` odbieranie plików z treminalu. Trzeba skonfigurować odpowiedni port USB
 
`zsend.sh` wysyłka plików z treminalu. Trzeba skonfigurować odpowiedni port USB

- LED Test

Program mrugający diodą LED 

**Uwaga** trzeba użyć kompilatora skrośnego: `arm-linux-gnueabihf-gcc -o led-blinking led-blinking.c`!  

- BRAM

Program obsługujący operację zapisu/odczytu do bloków BRAM, użycie:

```
Program to manage BRAM memory block. Usage:
           ./bram [bram.conf] --MODE
           [bram.conf] config file location, if location will not be provided, program will search file in current location
           --------------- MODES ---------------
           -r [OFFSET] [SIZE] read memory block, if none of additional options will be provided, all BRAM block will be printed
               OFFSET (num of bytes from starting address), starting position to read the data
               SIZE (num of bytes), how big block to read should be
               
           -w VALUE [OFFSET] write to memory
                VALUE in hex to put in memory
                OFFSET address relative to BRAM staring position, where value will be set. Smallest block is byte.
                
           -c clears BRAM
           
           Examples of use:
           -receive data, no offset, 24 bytes block data: ./bram -r 0 24
           -writes bytes into memory: ./bram -w 0x50 1020
           -clear BRAM and read config from different file: ./bram bram-test.conf -c
```
