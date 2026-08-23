#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include "../file_info.h"

int parse_cli(int argc, char *argv[], file_info_t *file_info)
{
    int opt;

    while ((opt = getopt(argc, argv, "r:h")) != -1)
    {
        switch (opt)
        {
        case 'r':
            file_info->path = optarg;
            break;
        case 'h':
            printf("\n");
            printf("    Usage: %s -r <file.pcap> [-c <packet_count>]\n", argv[0]);
            printf("    Options:\n");
            printf("      -r    Path to the pcap file to read\n");
            printf("      -c    Number of packets to process (default: all)\n");
            printf("      -h    Show this help message\n");
            printf("\n");
            return 0;
        default:
            fprintf(stderr, "Unknown option\n Use -h for help.\n");
            return -1;
        }
    }

    if (file_info->path == NULL)
    {
        fprintf(stderr, "Missing required -r <file.pcap> argument.\n");
        return -1;
    }

    printf("file_path=%s\n", file_info->path);
    return 1;
}
