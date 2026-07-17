#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "endian.h"
#include "protocols.h"
#include "protocol_swap.h"
#include "protocol_parser/protocol_parser.h"

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

void read_packets(FILE *fp, uint32_t data_link_type, uint32_t magic_number)
{
    pcap_packet_header_t packet_header;

    unsigned int packet_counter = 0;
    size_t remaining_payload = 0;
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

        /*packet_header_reader.c*/

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
            /*sll2_header_reader()*/

            if (sll2_header.protocol_type == 0x800) // ipv4*
            {

                ipv4_header_t ipv4_header;

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
                /*ipv4_header_reader()*/

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
                    /*tcp_header_reader.c*/
                }
            }

            long pos = ftell(fp);
            printf("\n------>Position in file = %ld\n\n", pos);

            // fseek(fp, remaining_payload, SEEK_CUR);
            break;

        default:
            printf("Unsupported Link Type!\n");
            fseek(fp, packet_header.incl_len, SEEK_CUR);
            break;
        }
        /* parse_data_link_layer.c*/
    }
}