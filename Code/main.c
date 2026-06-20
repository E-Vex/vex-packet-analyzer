#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "file.h"

typedef struct __attribute__((packed))
{
    uint32_t magic_number;
    uint16_t major_version;
    uint16_t minor_version;
    uint32_t this_zone;
    uint32_t sigfigs;
    uint32_t snaplen;
    uint32_t network;

} pcap_global_header_t;

typedef struct __attribute__((packed))
{
    uint32_t ts_sec;
    uint32_t ts_usec;
    uint32_t incl_len;
    uint32_t orig_len;
} pcap_packet_header_t;

void revers_magic_number(uint32_t *M)
{
    uint8_t byte1;
    uint8_t byte2;
    uint8_t byte3;
    uint8_t byte4;

    byte1 = (*M >> 24) & 0xFF;
    byte2 = (*M >> 16) & 0xFF;
    byte3 = (*M >> 8) & 0xFF;
    byte4 = (*M >> 0) & 0xFF;

    *M = (byte4 << 24) |
         (byte3 << 16) |
         (byte2 << 8) |
         (byte1);
}

void check_magic_number(uint32_t *M)
{
    if (*M == 0xd4c3b2a1)
    {
        revers_magic_number(M);
    }
    else
    {
        printf("Error: the file is corrupted or is not a valid PCAP file\n");
        exit(1);
    }
}

int main()
{

    char *name = get_file_name();
    pcap_global_header_t global_header;
    pcap_packet_header_t packet_header;

    // int_Node *head = NULL;

    FILE *filePointer = import_file(name);
    if (filePointer == NULL)
    {
        exit(1);
        return 0;
    }

    // long pos = ftell(filePointer);
    // printf("\n------>Position in file = %ld\n\n", pos);

    fread(&global_header, sizeof(pcap_global_header_t), 1, filePointer);
    check_magic_number(&(global_header.magic_number));

    printf("Magic Number : 0x%X\n", global_header.magic_number);
    printf("Snaplen : 0x%X\n", global_header.snaplen);
    printf("Network : 0x%X\n", global_header.network);

    unsigned int i = 0;
    while (fread(&packet_header, sizeof(pcap_packet_header_t), 1, filePointer) != 0)
    {

        printf("Packet Header : %d\n", i);
        printf("Packet Size   : %d\n", packet_header.incl_len);
        i++;

        fseek(filePointer, packet_header.incl_len, SEEK_CUR);
    }

    fclose(filePointer);
    return 0;
}