#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "protocols.h"
#include "protocol_swap.h"
#include "endian.h"
#include "packet_context.h"

void parse_sll2_header(packet_context_t *ctx)
{
    sll2_header_t sll2_header;
    fread(&sll2_header, sizeof(sll2_header_t), 1, ctx->fp);

    if (ctx->host_endianness == 1) /* if the host computer is little endain we have to swap every field the be in the correct network byte order */
        swap_sll2_header(&sll2_header);

    ctx->next_protocol = sll2_header.protocol_type;
}