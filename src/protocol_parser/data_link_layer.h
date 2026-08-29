#ifndef DATA_LINK_LAYER_H
#define DATA_LINK_LAYER_H

/* Standard library */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Project headers */
#include "endian.h"
#include "packet_context.h"
#include "protocols.h"
#include "protocol_swap.h"

void parse_sll2_header(packet_context_t *ctx);

#endif