#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <ctype.h>
#include "protocols.h"

void print_packet_header(pcap_packet_header_t *packet_header);
void print_ipv4_header(ipv4_header_t *ipv4_header);
void print_global_header(pcap_global_header_t *global_header);
void print_tcp_header(tcp_header_t *tcp_header);
int print_payload(FILE *fp, size_t remaining_payload);

#endif
