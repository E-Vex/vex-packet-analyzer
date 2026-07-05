#include <stdio.h>

FILE *import_binary_file(char filename[15])
{
    FILE *filePointer = fopen(filename, "rb");
    if (filePointer == NULL)
    {
        printf("Failed to open the file <NULL>\n");

        return NULL;
    }
    return filePointer;
}
char *get_file_name()
{
    static char file_name[16];

    printf("Enter the file name you want to display: ");
    if (scanf("%15s", file_name) != 1)
    {
        return NULL;
    }

    return file_name;
}
