#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include "../file_info.h"

int parse_cli(int argc, char *argv[], file_info_t *file_info)
{
    int opt;

    while ((opt = getopt(argc, argv, "r:")) != -1)
    {
        switch (opt)
        {
        case 'r':
            file_info->path = optarg;
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

    printf("file_path=%s\n", file_info->path);
    return 1;
}
