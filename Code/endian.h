#ifndef SWAP_H
#define SWAP_H

#include <stdio.h>
#include <stdint.h>
#include "protocols.h"

void swap_bytes(void *data, size_t size);
void swap_global_header(pcap_global_header_t *global_header);
void swap_packet_header(pcap_packet_header_t *packet_header);

#endif