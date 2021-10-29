//
// Created by redstart on 10/28/21.
//


#include "ring_buffer.h"

RingBuffer *buffer_init(void){
    RingBuffer *ringBuffer = calloc(1, sizeof(RingBuffer));
    ringBuffer->tail = NULL;
    ringBuffer->head = NULL;
    ringBuffer->count = 0;
    ringBuffer->max = RBUFFER_SIZE;
    return ringBuffer;
}

bool buffer_is_empty(RingBuffer *ringBuffer){
    return ringBuffer->count == 0 && !ringBuffer->head && !ringBuffer->tail;
}

bool buffer_is_full(RingBuffer *ringBuffer){
    return ringBuffer->count >= ringBuffer->max;
}

void buffer_add(RingBuffer *ringBuffer, Stats *stats){
    if (!buffer_is_full(ringBuffer)){
        if (ringBuffer->count == 0){
            ringBuffer->tail = stats;
            ringBuffer->head = stats;
        }else{
            Stats *prev_tail = ringBuffer->tail;
            ringBuffer->tail = stats;
            prev_tail->next = ringBuffer->tail;
        }
        ringBuffer->count++;

    }
}

Stats *buffer_get(RingBuffer *ringBuffer){
    if (!buffer_is_empty(ringBuffer)){
        return ringBuffer->head;
    }
    return NULL;
}

void buffer_remove(RingBuffer *ringBuffer){
    if (!buffer_is_empty(ringBuffer)){
        if (ringBuffer->tail == ringBuffer->head){
            free(ringBuffer->head);
            ringBuffer->head = NULL;
            ringBuffer->tail = NULL;
        }else {
            Stats *next_stat = ringBuffer->head->next;
            Stats *current_head = ringBuffer->head;
            ringBuffer->head = next_stat;
            free(current_head);
            current_head = NULL;
        }
        ringBuffer->count--;

    }
}

void buffer_flush(RingBuffer *ringBuffer){
    while (!buffer_is_empty(ringBuffer)){
        buffer_remove(ringBuffer);
    }
}