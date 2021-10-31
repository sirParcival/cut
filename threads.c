//
// Created by redstart on 10/28/21.
//

#include <asm-generic/errno.h>
#include "threads.h"

volatile sig_atomic_t done = 0;

typedef struct prev_data {
    int PrevIdle, PrevNonIdle, PrevTotal;
}prev_data;

void term(int signum)
{
    done = 1;
    printf("Received SIGTERM, flushing\n");
    buffer_flush(&raw_data);

}

void *Reader(void* arg) {
    const char* filename = "/proc/stat";
    FILE *file;

    regex_t regex;
    regcomp(&regex, "cpu", 0);

    while (!done){
        file = fopen(filename, "r");
        if (!file){
            return NULL;
        }
        size_t name_size = 4;

        char *name = calloc(name_size, sizeof(char ));
        fscanf(file, "%s", name);
        while (regexec(&regex, name, 0, NULL, 0) == 0){

            Stats *stats = calloc(1, sizeof(Stats));
            for (int i = 0; i < DATA_LENGTH; ++i) {
                fscanf(file, "%d", &stats->data[i]);
            }

            for (int i = 0; i < (int)name_size; ++i) {
                stats->name[i] = *(name+i);
            }

            pthread_mutex_lock(&mutex);
            buffer_add(&raw_data, stats);
            pthread_mutex_unlock(&mutex);



            fscanf(file, "%s", name);

        }
        sleep(1);
        free(name);
        name = NULL;
        fclose(file);

    }

    return NULL;
}

void calculate_total(int *Idle, int *NonIdle, int *Total, Stats *stats){
    *Idle = stats->data[0] + stats->data[1];
    for (int i = 2; i < DATA_LENGTH; ++i) {
        *NonIdle += stats->data[i];
    }
    *Total = *Idle + *NonIdle;
}

int get_index(Stats *stats){
    if(stats->name[3] == '\0'){
        return 0;
    }else{
        return (stats->name[3])-47;
    }
}


void *Analyzer(const int *num_of_cpus){
    int Idle, NonIdle, Total, totald, idled;
    prev_data *all_data = calloc((*num_of_cpus) + 1, sizeof(prev_data));
    prev_data *data;
    while (!done){
        pthread_mutex_lock(&mutex);
        Stats *stats = buffer_get(&raw_data);
        pthread_mutex_unlock(&mutex);
        if(!stats){
            continue;
        }
        data = &all_data[get_index(stats)];
        if (!data->PrevTotal && !data->PrevNonIdle && !data->PrevIdle){
            calculate_total(&data->PrevIdle, &data->PrevNonIdle, &data->PrevTotal, stats);
            pthread_mutex_lock(&mutex);
            buffer_remove(&raw_data);
            pthread_mutex_unlock(&mutex);
            continue;
        }

        calculate_total(&Idle, &NonIdle, &Total, stats);

        totald = Total - data->PrevTotal;
        idled = Idle - data->PrevIdle;

        pthread_mutex_lock(&mutex);
        stats->cpu_percentage = (double )(totald - idled) / totald;
        stats->cpu_percentage *= 100;
        pthread_mutex_unlock(&mutex);


    }

    return NULL;
}


void *Printer(void* arg) {
    while (!done){
        sleep(1);
        pthread_mutex_lock(&mutex);
        Stats *stats = buffer_get(&raw_data);
        pthread_mutex_unlock(&mutex);
        if (!stats){
            continue;
        }
        printf("%s: %.2f\n", stats->name, stats->cpu_percentage);

        pthread_mutex_lock(&mutex);
        buffer_remove(&raw_data);
        pthread_mutex_unlock(&mutex);

    }

    return NULL;
}
