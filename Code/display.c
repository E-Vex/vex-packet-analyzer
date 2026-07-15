#include <stdio.h>
#include <ctype.h>
#include "protocols.h"

void print_ipv4_header(ipv4_header_t *ipv4_header)
{
    printf("version_ihl : %d\n", ipv4_header->version_ihl);
    printf("tos : %d\n", ipv4_header->tos);
    printf("total_length : %d\n", ipv4_header->total_length);
    printf("identification : %d\n", ipv4_header->identification);
    printf("flags_fo : %d\n", ipv4_header->flags_fo);
    printf("ttl : %d\n", ipv4_header->ttl);

    if (ipv4_header->protocol == 6)
    {
        printf("protocol : TCP\n");
    }
    else
    {
        printf("protocol : %d\n", ipv4_header->protocol);
    }

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
    printf("source_port : %u\n", tcp_header->source_port);
    printf("dst_port : %u\n", tcp_header->dst_port);
    printf("seq_num : %u\n", tcp_header->seq_num);
    printf("ack_num : %u\n", tcp_header->ack_num);

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
    printf("window: %u\n", tcp_header->window);
    printf("checksum: %u\n", tcp_header->checksum);
    printf("urgent_ptr: %u\n", tcp_header->urgent_ptr);
}
int print_payload(FILE *fp, size_t remaining_payload)
{

    printf("\n--------------PAYLOAD--------------\n\n");

    uint8_t byte_of_data;
    uint8_t array_bytes_of_data[16];
    size_t chk = 0;
    int i = 0;

    if (remaining_payload == 0)
    {
        printf("There is no data to display\n");
    }
    else if (remaining_payload > 0)
    {
        while (chk < remaining_payload)
        {

            for (i = 0; i < 16; i++)
            {
                if (chk < remaining_payload)
                {
                    fread(&byte_of_data, sizeof(uint8_t), 1, fp);
                    chk += 1;
                    array_bytes_of_data[i] = byte_of_data;
                }
                else
                {
                    array_bytes_of_data[i] = 0x0;
                }
            }

            for (i = 0; i < 16; i++)
            {
                if (isprint(array_bytes_of_data[i]))
                {
                    printf("%c", array_bytes_of_data[i]);
                }
                else
                {
                    printf(".");
                }
            }

            printf("  |  ");

            for (int i = 0; i < 16; i++)
            {

                printf("%02X ", array_bytes_of_data[i]);
            }

            printf("\n");
        }
    }
    else
    {
        printf("Error! the file has been broken or it's corrupted\n");
        return 1;
    }

    return 0;
}
