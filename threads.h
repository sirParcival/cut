//
// Created by redstart on 10/28/21.
//

#ifndef CUT_THREADS_H
#define CUT_THREADS_H
#include <pthread.h>
#include <unistd.h>
#include <regex.h>
#include "buffer.h"
#include <signal.h>
#include <semaphore.h>

Buffer *raw_data;
Buffer *copy_data;
pthread_mutex_t mutex;

sem_t fillBuffer, fillCopy;
sem_t emptyBuffer, emptyCopy;

typedef struct prev_data {
    unsigned long PrevIdle, PrevNonIdle, PrevTotal;
}prev_data;


void *Reader(void *arg);
void *Analyzer(const int *num_of_cpus);
void *Printer(void *arg);

void term(int signum);

void read_to_buffer(char *name, regex_t *regex, FILE *file);

void analyze(prev_data *prevData, prev_data *all_data, unsigned long *Idle, unsigned long *NonIdle, unsigned long *Total);
int get_index(Stats *stats);
int write_previous_data(prev_data *prevData, Stats *stats);
void calculate_total(unsigned long *Idle, unsigned long *NonIdle, unsigned long*Total, Stats *stats);
void calculate_percentage(prev_data *prevData, const unsigned long *Idle, const unsigned long *Total, Stats *stats);

#endif //CUT_THREADS_H
