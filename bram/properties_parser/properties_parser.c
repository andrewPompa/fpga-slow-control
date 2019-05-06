#include <stdio.h>
#include <stdlib.h>

long get_address_offset(FILE *file)
{
    //TODO: dokończyć tą metodę!
    return 0x40000000;
}

long get_highest_address(FILE *conf_file_location)
{
    //TODO: dokończyć tą metodę!
    return 0x40001FFF;
}

//char szNumbers[] = "0x40000000";
//    char szNumbers2[] = "0x40001fff";
//    long int li1;
//    long int li4;
//    li4 = strtol (szNumbers,NULL,0);
//    li1 = strtol (szNumbers2,NULL,0);
//    char ch;
//
//    FILE *fp;
//
//    fp = fopen("/home/andrzej/fpga/fpga-slow-control/bram/bram.conf", "r");
//
//    if (fp == NULL)
//    {
//        perror("Error while opening the file.\n");
//        exit(EXIT_FAILURE);
//    }
//
//    while((ch = fgetc(fp)) != EOF)
//    {
//        printf("%c", ch);
//    }
//
//    fclose(fp);
//
//    printf ("from: %ld, to: %ld, difference is: %ld\n", li4, li1, (li1 - li4));

//   FILE *fp;
//    char *line = NULL;
//    size_t len = 0;
//    ssize_t read;
//
//    fp = fopen(file, "r");
//    if (fp == NULL)
//    {
//        return -1;
//    }
//
//    read = getline(&line, &len, fp);
//    while (read != -1)
//    {
//        printf("Retrieved line of length %zu :\n", read);
//        printf("%s\n", line);
//        read = getline(&line, &len, fp);
//    }
//
//    free(line);
//    exit(EXIT_SUCCESS);