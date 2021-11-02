
#include "threads.h"

int main() {
    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = term;
    sigaction(SIGTERM, &action, NULL);

    if (pthread_mutex_init(&mutex, NULL) != 0){
        printf("mutex failed\n");
    }
    int num_of_cpus = (int)sysconf(_SC_NPROCESSORS_ONLN);

//    if (buffer_init(&raw_data) != 0) printf("buffer with raw data failed to initialize\n");

    raw_data = calloc(1, sizeof(Buffer));
    copy_data = calloc(1, sizeof(Buffer));


    sem_init(&fillBuffer, 0, 0);
    sem_init(&fillCopy, 0, 0);
    sem_init(&emptyBuffer, 0, BUFFER_SIZE);
    sem_init(&emptyCopy, 0, BUFFER_SIZE);

    pthread_t reader, analyzer, printer;
    pthread_create(&reader, NULL, (void *(*)(void *)) Reader, NULL);
    pthread_create(&analyzer, NULL, (void *(*)(void *)) Analyzer, &num_of_cpus);
    pthread_create(&printer, NULL, (void *(*)(void *)) Printer, NULL);
//
    pthread_join(reader, NULL);
    pthread_join(analyzer, NULL);
    pthread_join(printer, NULL);

    printf("done\n");
    return 0;
}
