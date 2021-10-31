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

Buffer raw_data;
pthread_mutex_t mutex;

void *Reader(void *arg);
void *Analyzer(const int *num_of_cpus);
void *Printer(void *arg);
void term(int signum);
void calculate_total(int *Idle, int *NonIdle, int *Total, Stats *stats);
#endif //CUT_THREADS_H
