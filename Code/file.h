#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct int_Node
{
    int data;
    struct int_Node *next;
} int_Node;

int_Node *node_data(int data);
void traverse_list(int_Node *head);
void free_list(int_Node *head);
void insert_at_end(int_Node **headRef, int newData);
void print_list(int_Node *headRef);

FILE *import_file(const char *filename);
void read_file(FILE *filePointer, int_Node **headRef);

char *get_file_name(void);

#endif