#include <stdio.h>
#include <stdint.h>
#include "file.h"

typedef struct __attribute__((packed))
{
    uint32_t magic_number;
    uint16_t major_version;
    uint16_t minor_version;
    uint32_t this_zone;
    uint32_t sigfigs;
    uint32_t saplen;
    uint32_t network;

} pcap_global_header_t;

int main()
{
    char *name = get_file_name();

    int_Node *head = NULL;

    FILE *filePointer = import_file(name);
    read_file(filePointer, &head);
    fclose(filePointer);
}