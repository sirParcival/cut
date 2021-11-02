//
// Created by redstart on 10/28/21.
//


#include "buffer.h"

//int buffer_init(Buffer *buffer){
//    if(!buffer) return 1;
//    buffer->tail = NULL;
//    buffer->head = NULL;
//    buffer->count = 0;
//    buffer->max = BUFFER_SIZE;
//    return 0;
//}

bool buffer_is_empty(Buffer *buffer){
    return buffer->count == 0 && !buffer->head;
}

bool buffer_is_full(Buffer *buffer){
    return buffer->count >= buffer->max;
}

//void buffer_add(Buffer *buffer, Stats *stats){
//    if (!buffer_is_full(buffer)){
//        if (buffer->count == 0){
//            buffer->tail = stats;
//            buffer->head = stats;
//            buffer->tail->next = buffer->head;
//        }else{
//            Stats *prev_tail = buffer->tail;
//            stats->next = prev_tail->next;
//            buffer->tail = stats;
//            prev_tail->next = buffer->tail;
//        }
//
//        buffer->count++;
//    }else{
//        Stats *to_remove = buffer->tail->next;
//        stats->next = to_remove->next;
//        buffer->tail->next = stats;
//        buffer->tail = stats;
//        free(to_remove);
//        to_remove = NULL;
//    }
//}

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

//void buffer_remove(Buffer *buffer){
//    if (!buffer_is_empty(buffer)){
//        if (buffer->tail == buffer->head){
//            free(buffer->head);
//            buffer->head = NULL;
//            buffer->tail = NULL;
//        }else {
//            Stats *next_stat = buffer->head->next;
//            Stats *current_head = buffer->head;
//            buffer->head = next_stat;
//            buffer->tail = buffer->head;
//            free(current_head);
//            current_head = NULL;
//        }
//        buffer->count--;
//    }
//}

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
    buffer = NULL;
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
