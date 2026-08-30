/* Standard library */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

/* System / POSIX */
#include <getopt.h>
#include <unistd.h>

/* Project headers */
#include "../file_info.h"
#include "cli.h"

int parse_cli(int argc, char *argv[], file_info_t *file_info)
{
    int opt;
    file_info->packets_to_read = READ_ALL; /* default: reading the entire file  */

    while ((opt = getopt(argc, argv, "r:c:h")) != -1)
    {
        switch (opt)
        {
        case 'r':
            file_info->path = optarg;
            break;

        case 'c':
        {
            errno = 0;

            char *endptr;
            long count = strtol(optarg, &endptr, 10);

            if (errno == ERANGE)
            {
                printf("Error: out of range\n");
                errno = 0;
                return -1;
            }

            if (endptr == optarg || *endptr != '\0')
            {
                printf("Error: Input contains non-numeric characters \n");
                return -1;
            }

            if (count <= 0)
            {
                printf("Invalid input: packet count must be a positive integer.\n");
                return -1;
            }

            file_info->packets_to_read = count;
        }
        break;

        case 'h':
            printf("\n");
            printf("    Usage: %s -r <file.pcap> [-c <packets_to_read>]\n", argv[0]);
            printf("    Options:\n");
            printf("      -r    Path to the pcap file to read\n");
            printf("      -c    Number of packets to process (default: all)\n");
            printf("      -h    Show this help message\n");
            printf("\n");
            return 0;
            break;

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

    return 1;
}
