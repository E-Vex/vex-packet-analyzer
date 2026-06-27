#include <stdint.h>

/*--------------------------Structures-------------------------------*/
typedef struct __attribute__((packed)) // Global Header
{
    uint32_t magic_number;
    uint16_t major_version;
    uint16_t minor_version;
    uint32_t this_zone;
    uint32_t sigfigs;
    uint32_t snaplen;
    uint32_t network; // Data Link Type

} pcap_global_header_t;
typedef struct __attribute__((packed)) // Packet Header
{
    uint32_t ts_sec;
    uint32_t ts_usec;
    uint32_t incl_len;
    uint32_t orig_len;
} pcap_packet_header_t;
typedef struct __attribute__((packed)) // SLL2 Header
{
    uint16_t protocol_type;
    uint8_t skipped_data[18];

} sll2_header_t;
typedef struct __attribute__((packed)) // SLL Header
{

} sll_header_t;
typedef struct __attribute__((packed)) // Ethernet Header
{

} ethernet_header_t;
/*-------------------------------------------------------------------*/