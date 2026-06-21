#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include "file.h"
/*--------------------------Structures-------------------------------*/
typedef struct __attribute__((packed)) // Global Header
{
    uint32_t magic_number;
    uint16_t major_version;
    uint16_t minor_version;
    uint32_t this_zone;
    uint32_t sigfigs;
    uint32_t snaplen;
    uint32_t network;

} pcap_global_header_t;
typedef struct __attribute__((packed)) // Packet Header
{
    uint32_t ts_sec;
    uint32_t ts_usec;
    uint32_t incl_len;
    uint32_t orig_len;
} pcap_packet_header_t;
typedef struct __attribute__((packed)) // SLL2 Header
{
    uint8_t skipped_data[18];
    uint16_t protocol_type;
} sll2_header_t;
/*-------------------------------------------------------------------*/

typedef enum
{
    BIG,
    LITTLE
} endian_t;

/*--------------------------Functions-------------------------------*/
void check_file_pointer(FILE *fp)
{
    if (fp == NULL)
    {
        printf("Error: failed to open the file\n");
        exit(1);
    }
}
void swap_bytes(void *data, size_t size)
{
    uint8_t *bytes = (uint8_t *)data;

    uint8_t tmp;

    for (size_t i = 0; i < size / 2; i++)
    {
        tmp = bytes[i];
        bytes[i] = bytes[size - 1 - i];
        bytes[size - 1 - i] = tmp;
    }
}
int check_magic_number(uint32_t *M)
{
    uint8_t *b = (uint8_t *)M;

    if (b[0] == 0xa1 && b[1] == 0xb2 && b[2] == 0xc3 && b[3] == 0xd4)
    {
        return LITTLE;
    }
    else if (b[0] == 0xd4 && b[1] == 0xc3 && b[2] == 0xb2 && b[3] == 0xa1)
    {
        return BIG;
    }
    else
    {
        printf("Error: the file is corrupted or is not a valid PCAP file\n");
        exit(1);
    }
}
void read_packet_header(FILE *fp)
{
    pcap_packet_header_t packet_header;
    unsigned int i = 0;
    while (fread(&packet_header, sizeof(pcap_packet_header_t), 1, fp) != 0)
    {

        printf("Packet Header : %d\n", i);
        printf("Packet Size   : %d\n", packet_header.incl_len);
        i++;

        fseek(fp, packet_header.incl_len, SEEK_CUR);
    }
}
/*------------------------------------------------------------------*/

int main()
{
    pcap_global_header_t global_header;
    pcap_packet_header_t packet_header;
    sll2_header_t sll2_header;

    char *name = get_file_name();

    FILE *filePointer = import_file(name);
    check_file_pointer(filePointer);

    fread(&global_header, sizeof(pcap_global_header_t), 1, filePointer);
    check_magic_number(&(global_header.magic_number));

    printf("Magic Number : 0x%X\n", global_header.magic_number);
    printf("Snaplen : 0x%X\n", global_header.snaplen);
    printf("Network : 0x%X\n", global_header.network);

    /* if (global_header.network == 0x114)
     {
         fread(&sll2_header, sizeof(sll2_header_t), 1, filePointer);
     }*/

    // read_packet_header(filePointer);

    fclose(filePointer);
    return 0;
}

//
//
/*------------------Print the position in the file------------------*/
// long pos = ftell(filePointer);
// printf("\n------>Position in file = %ld\n\n", pos);