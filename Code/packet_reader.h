#ifndef PACKET_READER_H
#define PACKET_READER_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "endian.h"
#include "display.h"
#include "protocols.h"
#include "protocol_swap.h"

void normalize_global_header(pcap_global_header_t *global_header);

void read_packets(FILE *fp, uint32_t data_link_type, uint32_t magic_number);

#endif