#include <stdint.h>
#include <stddef.h>

typedef struct __attribute__((packed))
{
    size_t offset;
    size_t size;
} field_descriptor_t;

void swap_bytes(void *data, size_t size)
{
    uint8_t *bytes = (uint8_t *)data;

    uint8_t tmp;

    for (size_t i = 0; i < size / 2; i++)
    {
        tmp = bytes[i];
        bytes[i] = bytes[size - 1 - i];
        bytes[size - 1 - i] = tmp;
    }
}
/*---------------------------------------------------------------*/

void swap_fields(void *base, const field_descriptor_t *fields, size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        swap_bytes((uint8_t *)base + fields[i].offset, fields[i].size);
    }
}

/*---------------------------------------------------------------*/
