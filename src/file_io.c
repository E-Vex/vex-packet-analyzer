#include <stdio.h>
#include "file_io.h"
#include "file_info.h"

FILE *import_binary_file(const char *filename)
{
    FILE *filePointer = fopen(filename, "rb");
    if (filePointer == NULL)
    {
        printf("Failed to open the file <NULL>\n");

        return NULL;
    }
    return filePointer;
}

char *get_file_path(file_info_t *file_info)
{
    return file_info->path;
}
