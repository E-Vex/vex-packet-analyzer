#ifndef PACKET_CONTEXT_H
#define PACKET_CONTEXT_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

typedef struct
{
    FILE *fp;
    size_t remaining_payload;
    int host_endianness;

    uint32_t next_protocol;

} packet_context_t;

#endif