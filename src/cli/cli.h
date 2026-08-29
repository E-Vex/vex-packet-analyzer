#ifndef CLI_H
#define CLI_H

/* Project headers */
#include "../file_info.h"

#define READ_ALL -1

int parse_cli(int argc, char *argv[], file_info_t *file_info);

#endif