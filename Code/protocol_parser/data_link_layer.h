#ifndef DATA_LINK_LAYER_H
#define DATA_LINK_LAYER_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "protocols.h"
#include "protocol_swap.h"
#include "endian.h"
#include "packet_context.h"

void parse_sll2_header(packet_context_t *ctx);

#endif