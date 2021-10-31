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

typedef struct buffer{
    struct stats *tail;
    struct stats *head;
    int count;
    int max;
}Buffer;

typedef struct stats{
    struct stats *next;
    double cpu_percentage;
    int data[DATA_LENGTH];
    char name[8];
}Stats;



int buffer_init(Buffer *ringBuffer);
bool buffer_is_empty(Buffer *ringBuffer);
bool buffer_is_full(Buffer *ringBuffer);
void buffer_add(Buffer *ringBuffer, Stats *stats);
Stats *buffer_get(Buffer *ringBuffer);
void buffer_remove(Buffer *ringBuffer);
void buffer_flush(Buffer *buffer);
void stats_copy(Stats *destination, Stats *source);

#endif //CUT_BUFFER_H
