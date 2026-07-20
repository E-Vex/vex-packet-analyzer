#ifndef NETWORK_LAYER_H
#define NETWORK_LAYER_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "endian.h"
#include "protocols.h"
#include "packet_context.h"

void parse_ipv4_header(packet_context_t *ctx);

#endif