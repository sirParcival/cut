//
// Created by redstart on 10/28/21.
//

#ifndef CUT_BUFFER_H
#define CUT_BUFFER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define DATA_LENGTH 10
#define BUFFER_SIZE 2048
#define NAME_SIZE 8

typedef struct buffer{
    struct stats *tail;
    struct stats *head;
    int count;
    int max;
}Buffer;

typedef struct stats{
    struct stats *next;
    double cpu_percentage;
    unsigned long data[DATA_LENGTH];
    char name[NAME_SIZE];
}Stats;



//int buffer_init(Buffer *buffer);
bool buffer_is_empty(Buffer *buffer);
bool buffer_is_full(Buffer *buffer);
int put_into_buffer(Buffer *buffer, Stats *stats);
Stats *buffer_get(Buffer *buffer);
//void buffer_remove(Buffer *buffer);
int remove_from_buffer(Buffer *buffer);
void buffer_flush(Buffer **buffer);
void stats_copy(Stats *destination, Stats *source);

#endif //CUT_BUFFER_H
