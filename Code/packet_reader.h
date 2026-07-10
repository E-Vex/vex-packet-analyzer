#ifndef PACKET_READER_H
#define PACKET_READER_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "endian.h"
#include "protocols.h"
#include "protocol_swap.h"

void normalize_global_header(pcap_global_header_t *global_header);

void print_ipv4_header(ipv4_header_t *ipv4_header);
void print_global_header(pcap_global_header_t *global_header);
void print_packet_header(pcap_packet_header_t *packet_header);
void print_tcp_header(tcp_header_t *tcp_header);

void read_packets(FILE *fp, uint32_t data_link_type, uint32_t magic_number);

#endif