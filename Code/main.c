#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <arpa/inet.h>
#include "file_io.h"
#include "protocols.h"
#include "packet_reader.h"

/*--------------------------Functions-------------------------------*/
void check_file_pointer(FILE *fp)
{
    if (fp == NULL)
    {
        printf("Error: failed to open the file\n");
        exit(1);
    }
}

/*------------------------------------------------------------------*/

int main()
{
    pcap_global_header_t global_header;
    pcap_packet_header_t packet_header;

    /*---------------------------------------------------------------*/
    char *name = get_file_name();

    FILE *filePointer = import_binary_file(name);
    check_file_pointer(filePointer);

    fread(&global_header, sizeof(pcap_global_header_t), 1, filePointer);

    printf("\n----------------\n\n");

    read_packets(filePointer, global_header.network, global_header.magic_number);

    fclose(filePointer);
    return 0;
}

//
//
/*------------------Print the position in the file------------------*/
// long pos = ftell(filePointer);
// printf("\n------>Position in file = %ld\n\n", pos);