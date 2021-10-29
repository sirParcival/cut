//
// Created by redstart on 10/28/21.
//

#ifndef CUT_RING_BUFFER_H
#define CUT_RING_BUFFER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define RBUFFER_SIZE 512

typedef struct ringbuffer{
    struct stats *tail;
    struct stats *head;
    int count;
    int max;
}RingBuffer;

typedef struct stats{
    struct stats *next;
    int user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
}Stats;



RingBuffer *buffer_init(void);
bool buffer_is_empty(RingBuffer *ringBuffer);
bool buffer_is_full(RingBuffer *ringBuffer);
void buffer_add(RingBuffer *ringBuffer, Stats *stats);
Stats *buffer_get(RingBuffer *ringBuffer);
void buffer_remove(RingBuffer *ringBuffer);
void buffer_flush(RingBuffer **ringBuffer);

#endif //CUT_RING_BUFFER_H
