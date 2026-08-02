#ifndef SWAP_H
#define SWAP_H

#include <stdint.h>
#include <stddef.h>

typedef struct __attribute__((packed))
{
    size_t offset;
    size_t size;
} field_descriptor_t;

void swap_bytes(void *data, size_t size);
void swap_fields(void *base, const field_descriptor_t *fields, size_t count);

/*--------------------------------------------------------------------------------*/
uint8_t *magic_number_as_bytes(uint32_t *magic_number);
int detect_pcap_endianness(uint8_t *b);
int detect_host_endianness(void);

#endif