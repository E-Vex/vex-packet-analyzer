#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "endian.h"
#include "protocols.h"
#include "protocol_swap.h"

#define LINKTYPE_ETHERNET 1
#define LINKTYPE_LINUX_SLL2 276
#define LINKTYPE_IEEE802_11 105
#define LINKTYPE_LINUX_SLL 113
#define LINKTYPE_NULL 0

void normalize_global_header(pcap_global_header_t *global_header)
{
    uint8_t *b = (uint8_t *)&global_header->magic_number;
    if (b[0] == 0xa1 && b[1] == 0xb2 && b[2] == 0xc3 && b[3] == 0xd4)
    {
        swap_global_header(global_header);
    }
    else if (b[0] == 0xd4 && b[1] == 0xc3 && b[2] == 0xb2 && b[3] == 0xa1)
    {
        // no swap needed
    }
    else
    {
        printf("Error: the file is corrupted or is not a valid PCAP file\n");
        exit(1);
    }
}

void print_ipv4_header(ipv4_header_t *ipv4_header)
{
    printf("version_ihl : %d\n", ipv4_header->version_ihl);
    printf("tos : %d\n", ipv4_header->tos);
    printf("total_length : %d\n", ipv4_header->total_length);
    printf("identification : %d\n", ipv4_header->identification);
    printf("flags_fo : %d\n", ipv4_header->flags_fo);
    printf("ttl : %d\n", ipv4_header->ttl);
    printf("protocol : %d\n", ipv4_header->protocol);
    printf("checksum : %d\n", ipv4_header->checksum);

    uint8_t *src = (uint8_t *)&ipv4_header->src_ip;
    printf("src_ip : %d.%d.%d.%d\n", src[0], src[1], src[2], src[3]);
    uint8_t *dst = (uint8_t *)&ipv4_header->dst_ip;
    printf("dst_ip : %d.%d.%d.%d\n", dst[0], dst[1], dst[2], dst[3]);
}
void print_global_header(pcap_global_header_t *global_header)
{
    printf("Magic Number : 0x%X\n", global_header->magic_number);
    printf("Major Version : %d\n", global_header->major_version);
    printf("Minor Version : %d\n", global_header->minor_version);
    printf("This Zone : %d\n", global_header->this_zone);
    printf("Sigfigs : %d\n", global_header->sigfigs);
    printf("Snaplen : %d\n", global_header->snaplen);
    printf("Network : 0x%X\n", global_header->network);
}
void print_packet_header(pcap_packet_header_t *packet_header)
{
    printf("ts_sec : %d\n", packet_header->ts_sec);
    printf("ts_usec : %d\n", packet_header->ts_usec);
    printf("incl_len : %d\n", packet_header->incl_len);
    printf("orig_len : %d\n", packet_header->orig_len);
}
void print_tcp_header(tcp_header_t *tcp_header)
{
    printf("source_port : %d\n", tcp_header->source_port);
    printf("dst_port : %d\n", tcp_header->dst_port);
    printf("seq_num : %d\n", tcp_header->seq_num);
    printf("ack_num : %d\n", tcp_header->ack_num);

    printf("offset : 0x%X\n", (tcp_header->offset_reserved >> 4) & 0x0F);
    printf("reserved : 0x%X\n", ((tcp_header->offset_reserved)) & 0x0F);

    printf("TCP Flags: ");
    /*Bit Number :
     7    6    5    4    3    2    1    0
    +----+----+----+----+----+----+----+----+
    |CWR |ECE |URG |ACK |PSH |RST |SYN |FIN |
    +----+----+----+----+----+----+----+----+*/

    if (tcp_header->flags & 0x02)
        printf("SYN ");

    if (tcp_header->flags & 0x10)
        printf("ACK ");

    if (tcp_header->flags & 0x01)
        printf("FIN ");

    if (tcp_header->flags & 0x04)
        printf("RST ");

    printf("\n");

    printf("----------------\n");
    printf("window: %d\n", tcp_header->window);
    printf("checksum: %d\n", tcp_header->checksum);
    printf("urgent_ptr: %d\n", tcp_header->urgent_ptr);
}

void read_packets(FILE *fp, uint32_t data_link_type, uint32_t magic_number)
{
    pcap_packet_header_t packet_header;

    unsigned int packet_counter = 0;
    int remaining_payload = 0;
    while (packet_counter < 3 && fread(&packet_header, sizeof(pcap_packet_header_t), 1, fp) == 1)
    {
        remaining_payload = 0;

        packet_counter++;

        uint8_t *b = (uint8_t *)&magic_number;
        if (b[0] == 0xa1 && b[1] == 0xb2 && b[2] == 0xc3 && b[3] == 0xd4)
        {
            swap_packet_header(&packet_header);
        }

        remaining_payload += packet_header.incl_len;

        printf("packet : %d\n", packet_counter);
        printf("Captured Length: %d bytes\n", packet_header.incl_len);

        switch (data_link_type)
        {
        case LINKTYPE_ETHERNET:
            ethernet_header_t ethernet_header;
            break;

        case LINKTYPE_LINUX_SLL:
            sll_header_t sll_header;
            break;

        case LINKTYPE_LINUX_SLL2:
            sll2_header_t sll2_header;
            int ipv4_header_len = 0;
            int tcp_header_len = 0;

            fread(&sll2_header, sizeof(sll2_header_t), 1, fp);

            swap_bytes(&sll2_header.protocol_type, sizeof(sll2_header.protocol_type));

            remaining_payload -= sizeof(sll2_header);

            printf("SLL2 data link type\n");

            if (sll2_header.protocol_type == 0x800) // ipv4*
            {

                ipv4_header_t ipv4_header;

                printf("protocol : 0x%X --> IPv4\n", sll2_header.protocol_type);

                fread(&ipv4_header, sizeof(ipv4_header_t), 1, fp);

                swap_ipv4_header(&ipv4_header);

                ipv4_header_len = (ipv4_header.version_ihl & 0x0F) * 4;
                if (ipv4_header_len > 20)
                {
                    fseek(fp, (ipv4_header_len - 20), SEEK_CUR);
                    remaining_payload -= ipv4_header_len;
                }
                else
                {
                    remaining_payload -= 20;
                }

                printf("\n--------------IPv4--------------\n\n");
                print_ipv4_header(&ipv4_header);

                if (ipv4_header.protocol == 6) // TCP
                {

                    tcp_header_t tcp_header;

                    fread(&tcp_header, sizeof(tcp_header_t), 1, fp);

                    swap_tcp_header(&tcp_header);

                    tcp_header_len = ((tcp_header.offset_reserved >> 4) & 0x0F) * 4;
                    if (tcp_header_len > 20)
                    {
                        fseek(fp, (tcp_header_len - 20), SEEK_CUR);
                        remaining_payload -= tcp_header_len;
                    }
                    else
                    {
                        remaining_payload -= 20;
                    }

                    printf("\n--------------TCP--------------\n\n");
                    print_tcp_header(&tcp_header);
                }
            }

            long pos = ftell(fp);
            printf("\n------>Position in file = %ld\n\n", pos);

            fseek(fp, remaining_payload, SEEK_CUR);
            break;

        default:
            printf("Unsupported Link Type!\n");
            fseek(fp, packet_header.incl_len, SEEK_CUR);
            break;
        }
    }
}