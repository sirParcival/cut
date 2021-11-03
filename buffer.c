//
// Created by redstart on 10/28/21.
//


#include "buffer.h"


bool buffer_is_empty(Buffer *buffer){
    return buffer->count == 0 && !buffer->head;
}

bool buffer_is_full(Buffer *buffer){
    return buffer->count >= buffer->max;
}

int put_into_buffer(Buffer *buffer, Stats *stats){
    if(buffer->count < BUFFER_SIZE){
        if(buffer->count == 0){
            buffer->head = stats;
            buffer->tail = stats;
        }else{
            buffer->tail->next = stats;
            buffer->tail = stats;
        }
        buffer->count++;
        return 0;
    }
    return 1;
}

Stats *buffer_get(Buffer *buffer){
    if (!buffer_is_empty(buffer)){
        return buffer->head;
    }
    return NULL;
}


int remove_from_buffer(Buffer *buffer){
    if(buffer->count > 0){
        Stats *head = buffer->head;
        buffer->head = buffer->head->next;
        free(head);
        head = NULL;
        if (buffer->count == 1){
            buffer->tail = NULL;
        }
        buffer->count--;
        return 0;
    }
    return 1;
}

void buffer_flush(Buffer **buffer){
    while ((*buffer)->count > 0){
        remove_from_buffer(*buffer);
    }
    free(*buffer);
    *buffer = NULL;
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
