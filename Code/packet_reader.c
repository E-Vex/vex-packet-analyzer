#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "endian.h"
#include "protocols.h"
#include "protocol_swap.h"
#include "protocol_parser/protocol_parser.h"
#include "packet_context.h"

#define LINKTYPE_ETHERNET 1
#define LINKTYPE_LINUX_SLL2 276
#define LINKTYPE_IEEE802_11 105
#define LINKTYPE_LINUX_SLL 113
#define LINKTYPE_NULL 0

void read_packets(FILE *fp, uint32_t data_link_type, uint32_t magic_number)
{
    pcap_packet_header_t packet_header;
    packet_context_t ctx;

    unsigned int packet_counter = 0;

    while (packet_counter < 3 && fread(&packet_header, sizeof(pcap_packet_header_t), 1, fp) == 1)
    {
        ctx.remaining_payload = 0;
        ctx.fp = fp;
        packet_counter++;

        /*-----------------------------------------------------*/
        uint8_t *bytes = magic_number_as_bytes(&magic_number);
        int pcap_endian = detect_pcap_endianness(bytes);
        ctx.host_endianness = detect_host_endianness();
        if (pcap_endian != ctx.host_endianness)
            swap_packet_header(&packet_header);
        /*-----------------------------------------------------*/

        ctx.remaining_payload += packet_header.incl_len;

        switch (data_link_type)
        {
        case LINKTYPE_ETHERNET:
            ethernet_header_t ethernet_header;
            break;

        case LINKTYPE_LINUX_SLL:
            sll_header_t sll_header;
            break;

        case LINKTYPE_LINUX_SLL2:

            parse_sll2_header(&ctx);
            ctx.remaining_payload -= sizeof(sll2_header_t);

            if (ctx.next_protocol == 0x800) // ipv4*
            {
                parse_ipv4_header(&ctx);

                if (ctx.next_protocol == 6) // TCP
                {
                    int tcp_header_len = 0;
                    tcp_header_t tcp_header;

                    fread(&tcp_header, sizeof(tcp_header_t), 1, fp);

                    swap_tcp_header(&tcp_header);

                    tcp_header_len = ((tcp_header.offset_reserved >> 4) & 0x0F) * 4;
                    if (tcp_header_len > 20)
                    {
                        fseek(fp, (tcp_header_len - 20), SEEK_CUR);
                        ctx.remaining_payload -= tcp_header_len;
                    }
                    else
                    {
                        ctx.remaining_payload -= 20;
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