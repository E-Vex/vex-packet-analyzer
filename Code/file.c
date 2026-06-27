#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct int_Node
{
    int data;
    struct int_Node *next;

} int_Node;

int_Node *node_data(int data)
{

    int_Node *node = malloc(sizeof(int_Node));
    if (node == NULL)
    {
        printf("Error: out of memory\n");
        exit(1);
    }
    else
    {
        node->data = data;
        node->next = NULL;
    }

    return node;
}
void traverse_list(int_Node *head)
{
    int_Node *currentPointer = head;
    int i = 1;
    while (currentPointer != NULL)
    {
        printf("Node %d : %d\n", i, currentPointer->data);
        currentPointer = currentPointer->next;
        i++;
    }
}
void free_list(int_Node *head)
{
    int_Node *copyPointer = head;
    int_Node *currentPointer = head;
    while (currentPointer != NULL)
    {
        copyPointer = currentPointer->next;
        free(currentPointer);
        currentPointer = copyPointer;
    }
}

void insert_at_end(int_Node **headRef, int newData)
{
    int_Node **currentPointer = headRef;
    if (*headRef == NULL)
    {
        *headRef = node_data(newData);
        return;
    }
    while (1)
    {
        if ((*currentPointer)->next == NULL)
        {
            (*currentPointer)->next = node_data(newData);
            break;
        }
        currentPointer = &((*currentPointer)->next);
    }
}

void print_list(int_Node *headRef)
{
    int_Node *currentPointer = headRef;
    printf("--------------------Data--------------------\n");
    while (currentPointer != NULL)
    {

        printf("%d\n", currentPointer->data);
        currentPointer = currentPointer->next;
    }
    printf("NULL\n");
}

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

void read_file(FILE *filePointer, int_Node **headRef)
{
    int num;
    int result;
    while ((result = fscanf(filePointer, "%d", &num)) != EOF)
    {

        if (result == 1)
        {
            insert_at_end(headRef, num);
        }
        else if (result == 0)
        {
            printf("\n               the operation stoped!\n");
            printf("The file is contains texts between the numbers\n\n");
            break;
        }
    }
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
