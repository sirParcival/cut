//
// Created by redstart on 10/28/21.
//


#include "buffer.h"

int buffer_init(Buffer *buffer){
    if(!buffer) return 1;
    buffer->tail = NULL;
    buffer->head = NULL;
    buffer->count = 0;
    buffer->max = BUFFER_SIZE;
    return 0;
}

bool buffer_is_empty(Buffer *buffer){
    return buffer->count == 0 && !buffer->head;
}

bool buffer_is_full(Buffer *buffer){
    return buffer->count >= buffer->max;
}

void buffer_add(Buffer *buffer, Stats *stats){
    if (!buffer_is_full(buffer)){
        if (buffer->count == 0){
            buffer->tail = stats;
            buffer->head = stats;

        }else{
            Stats *prev_tail = buffer->tail;
            buffer->tail = stats;
            prev_tail->next = buffer->tail;
        }

        buffer->count++;
    }else{
        free(stats);
        stats = NULL;
    }
}

Stats *buffer_get(Buffer *buffer){
    if (!buffer_is_empty(buffer)){
        return buffer->head;
    }
    return NULL;
}

void buffer_remove(Buffer *buffer){
    if (!buffer_is_empty(buffer)){
        if (buffer->tail == buffer->head){
            free(buffer->head);
            buffer->head = NULL;
            buffer->tail = NULL;
        }else {
            Stats *next_stat = buffer->head->next;
            Stats *current_head = buffer->head;
            buffer->head = next_stat;
            buffer->tail = buffer->head;
            free(current_head);
            current_head = NULL;
        }
        buffer->count--;
    }
}

void buffer_flush(Buffer *buffer){
    while (!buffer_is_empty(buffer)){
        buffer_remove(buffer);
    }
    printf("removed\n");
}

void stats_copy(Stats *destination, Stats *source){
    for (int i = 0; i < 8; ++i){
        destination->name[i] = source->name[i];
    }
    for (int i = 0; i < DATA_LENGTH; ++i) {
        destination->data[i] = source->data[i];
    }
}
