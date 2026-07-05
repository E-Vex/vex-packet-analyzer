#include <stdio.h>
#include <stdint.h>
#include "protocols.h"

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