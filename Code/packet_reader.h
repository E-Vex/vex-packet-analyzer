#ifndef PACKET_READER_H
#define PACKET_READER_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "endian.h"
#include "protocols.h"
#include "protocol_swap.h"
#include "protocol_parser/protocol_parser.h"
#include "packet_context.h"

void read_packets(FILE *fp, uint32_t data_link_type, uint32_t magic_number);

#endif