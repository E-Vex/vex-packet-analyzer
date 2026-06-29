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
typedef struct __attribute__((packed)) // IPv4 Header
{
    uint8_t version_ihl;     // Version (4 bits) + Internet Header Length (4 bits)
    uint8_t tos;             // Type of Service
    uint16_t total_length;   // Total Length of the IP packet
    uint16_t identification; // Identification
    uint16_t flags_fo;       // Flags (3 bits) + Fragment Offset (13 bits)
    uint8_t ttl;             // Time to Live
    uint8_t protocol;        // Protocol (TCP=6, UDP=17)
    uint16_t checksum;       // Header Checksum
    uint32_t src_ip;         // Source IP Address
    uint32_t dst_ip;         // Destination IP Address
} ipv4_header_t;
typedef struct __attribute__((packed)) // TCP Header (prototype)
{
    uint16_t source_port;
    uint16_t dest_port;
    uint32_t seq_num;
    uint32_t ack_num;
    uint8_t offset_reserved;
    uint8_t flags;
    uint16_t window;
    uint16_t checksum;
    uint16_t urgent_ptr;
} tcp_header_t;

/*-------------------------------------------------------------------*/