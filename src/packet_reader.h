#ifndef PACKET_READER_H
#define PACKET_READER_H

/* Standard library */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Project headers */
#include "endian.h"
#include "packet_context.h"
#include "protocols.h"
#include "protocol_swap.h"
#include "protocol_parser/protocol_parser.h"

void read_packets(FILE *fp, uint32_t data_link_type, uint32_t magic_number, file_info_t *file_info);

#endif