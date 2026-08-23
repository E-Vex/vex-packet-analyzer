#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include "file_info.h"

FILE *import_binary_file(const char *filename);
char *get_file_path(file_info_t *file_info);

#endif