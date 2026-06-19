#include <stdio.h>
#include <stdint.h>
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
} pacp_packet_header_t;

int main()
{
    char *name = get_file_name();
    pcap_global_header_t global_header;

    int_Node *head = NULL;

    FILE *filePointer = import_file(name);
    fread(&global_header, sizeof(pcap_global_header_t), 1, filePointer);
    printf("Magic Number : 0x%X\n", global_header.magic_number);
    printf("Snaplen : 0x%X\n", global_header.snaplen);
    printf("Network : 0x%X\n", global_header.network);
    fclose(filePointer);
}