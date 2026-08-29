#ifndef NETWORK_LAYER_H
#define NETWORK_LAYER_H

/* Standard library */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Project headers */
#include "endian.h"
#include "packet_context.h"
#include "protocols.h"

void parse_ipv4_header(packet_context_t *ctx);

#endif