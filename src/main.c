#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <arpa/inet.h>
#include "file_io.h"
#include "protocols.h"
#include "packet_reader.h"
#include "cli/cli.h"
#include "file_info.h"

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

int main(int argc, char *argv[])
{
    pcap_global_header_t global_header;
    pcap_packet_header_t packet_header;

    file_info_t file_info = {.path = NULL};

    /*---------------------------------------------------------------*/
    if (parse_cli(argc, argv, &file_info) != 1)
    {
        return 1;
    }

    FILE *filePointer = import_binary_file(file_info.path);
    check_file_pointer(filePointer);

    fread(&global_header, sizeof(pcap_global_header_t), 1, filePointer);

    uint8_t *bytes = magic_number_as_bytes(&(global_header.magic_number));
    int pcap_endian = detect_pcap_endianness(bytes);
    int host_endian = detect_host_endianness();

    if (pcap_endian != host_endian)
    {
        swap_global_header(&global_header);
    }

    printf("\n--------------------------------\n\n");

    read_packets(filePointer, global_header.network, global_header.magic_number);

    fclose(filePointer);
    return 0;
}

//
//
/*------------------Print the position in the file------------------*/
// long pos = ftell(filePointer);
// printf("\n------>Position in file = %ld\n\n", pos);