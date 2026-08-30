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

    while ((opt = getopt(argc, argv, ":r:c:h")) != -1)
    {
        switch (opt)
        {
        case 'r':
            if (file_info->path != NULL)
            {
                fprintf(stderr, "Error: Duplicate -r option\n");
                return -1;
            }

            file_info->path = optarg;
            break;

        case 'c':
        {
            if (file_info->packets_to_read != READ_ALL)
            {
                fprintf(stderr, "Error: Duplicate -c option\n");
                return -1;
            }

            errno = 0;

            char *endptr;
            long count = strtol(optarg, &endptr, 10);

            if (errno == ERANGE)
            {
                fprintf(stderr, "Error: out of range\n");
                errno = 0;
                return -1;
            }

            if (endptr == optarg || *endptr != '\0')
            {
                fprintf(stderr, "Error: Input contains non-numeric characters\n");
                return -1;
            }

            if (count <= 0)
            {
                fprintf(stderr, "Invalid input: packet count must be a positive integer\n");
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

        case ':':
            fprintf(stderr, "vetrix: error: option -%c requires an argument\n", optopt);
            return -1;
            break;

        case '?':
        default:
            fprintf(stderr,
                    "vetrix: error: unknown option '-%c'\n", optopt);
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
