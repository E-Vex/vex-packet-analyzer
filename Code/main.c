#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include "file.h"

#define LINKTYPE_ETHERNET 1
#define LINKTYPE_LINUX_SLL2 276
#define LINKTYPE_IEEE802_11 105
#define LINKTYPE_LINUX_SLL 113
#define LINKTYPE_NULL 0

/*--------------------------Structures-------------------------------*/
typedef struct __attribute__((packed)) // Global Header
{
    uint32_t magic_number;
    uint16_t major_version;
    uint16_t minor_version;
    uint32_t this_zone;
    uint32_t sigfigs;
    uint32_t snaplen;
    uint32_t network; // Data Link Type

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
    uint16_t protocol_type;
    uint8_t skipped_data[18];

} sll2_header_t;
typedef struct __attribute__((packed)) // SLL Header
{

} sll_header_t;
typedef struct __attribute__((packed)) // Ethernet Header
{

} ethernet_header_t;
/*-------------------------------------------------------------------*/

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
void swap_global_header(pcap_global_header_t *global_header)
{
    swap_bytes(&(global_header->magic_number), sizeof(global_header->magic_number));
    swap_bytes(&(global_header->major_version), sizeof(global_header->major_version));
    swap_bytes(&(global_header->minor_version), sizeof(global_header->minor_version));
    swap_bytes(&(global_header->this_zone), sizeof(global_header->this_zone));
    swap_bytes(&(global_header->sigfigs), sizeof(global_header->sigfigs));
    swap_bytes(&(global_header->snaplen), sizeof(global_header->snaplen));
    swap_bytes(&(global_header->network), sizeof(global_header->network));
}
void swap_packet_header(pcap_packet_header_t *packet_header)
{
    swap_bytes(&(packet_header->ts_sec), sizeof(packet_header->ts_sec));
    swap_bytes(&(packet_header->ts_usec), sizeof(packet_header->ts_usec));
    swap_bytes(&(packet_header->incl_len), sizeof(packet_header->incl_len));
    swap_bytes(&(packet_header->orig_len), sizeof(packet_header->orig_len));
}
void normalize_global_header(pcap_global_header_t *global_header)
{
    uint8_t *b = (uint8_t *)global_header->magic_number;
    if (b[0] == 0xa1 && b[1] == 0xb2 && b[2] == 0xc3 && b[3] == 0xd4)
    {
        swap_global_header(global_header);
    }
    else if (b[0] == 0xd4 && b[1] == 0xc3 && b[2] == 0xb2 && b[3] == 0xa1)
    {
        // no swap needed
    }
    else
    {
        printf("Error: the file is corrupted or is not a valid PCAP file\n");
        exit(1);
    }
}
void read_packets(FILE *fp, uint32_t data_link_type)
{
    pcap_packet_header_t packet_header;
    sll2_header_t sll2_header;
    sll_header_t sll_header;
    ethernet_header_t ethernet_header;

    unsigned int packet_counter = 0;

    while (fread(&packet_header, sizeof(pcap_packet_header_t), 1, fp) != 0)
    {
    }

    switch (data_link_type)
    {
    case LINKTYPE_ETHERNET:

        break;

    case LINKTYPE_LINUX_SLL:

        break;

    case LINKTYPE_LINUX_SLL2:

        break;

    default:
        printf("Unsupported Link Type!\n");
    }
}
void print_global_header(pcap_global_header_t *global_header)
{
    printf("Magic Number : 0x%X\n", global_header->magic_number);
    printf("Major Version : %d\n", global_header->major_version);
    printf("Minor Version : %d\n", global_header->minor_version);
    printf("This Zone : %d\n", global_header->this_zone);
    printf("Sigfigs : %d\n", global_header->sigfigs);
    printf("Snaplen : %d\n", global_header->snaplen);
    printf("Network : 0x%X\n", global_header->network);
}
void print_packet_header(pcap_packet_header_t *packet_header)
{
    printf("ts_sec : %d\n", packet_header->ts_sec);
    printf("ts_usec : %d\n", packet_header->ts_usec);
    printf("incl_len : %d\n", packet_header->incl_len);
    printf("orig_len : %d\n", packet_header->orig_len);
}

/*------------------------------------------------------------------*/

int main()
{
    pcap_global_header_t global_header;
    pcap_packet_header_t packet_header;
    sll2_header_t sll2_header;

    /*---------------------------------------------------------------*/
    char *name = get_file_name();

    FILE *filePointer = import_binary_file(name);
    check_file_pointer(filePointer);

    fread(&global_header, sizeof(pcap_global_header_t), 1, filePointer);

    fread(&packet_header, sizeof(pcap_packet_header_t), 1, filePointer);
    print_packet_header(&packet_header);

    fclose(filePointer);
    return 0;
}

//
//
/*------------------Print the position in the file------------------*/
// long pos = ftell(filePointer);
// printf("\n------>Position in file = %ld\n\n", pos);