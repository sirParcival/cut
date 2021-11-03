
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


    raw_data = calloc(1, sizeof(Buffer));
    copy_data = calloc(1, sizeof(Buffer));
    copy_data->max = BUFFER_SIZE;
    raw_data->max = BUFFER_SIZE;
    all_data = calloc((unsigned long )(num_of_cpus) + 1, sizeof(prev_data));

    sem_init(&fillBuffer, 0, 0);
    sem_init(&fillCopy, 0, 0);
    sem_init(&emptyBuffer, 0, BUFFER_SIZE);
    sem_init(&emptyCopy, 0, BUFFER_SIZE);

    pthread_t reader, analyzer, printer;
    pthread_create(&reader, NULL, (void *(*)(void *)) Reader, NULL);
    pthread_create(&analyzer, NULL, (void *(*)(void *)) Analyzer, NULL);
    pthread_create(&printer, NULL, (void *(*)(void *)) Printer, NULL);
//

    pthread_join(reader, NULL);
    printf("reader joined\n");
//    pthread_cancel(analyzer);
    pthread_join(analyzer, NULL);
    printf("analyzer joined\n");

    pthread_join(printer, NULL);
    printf("printer joined\n");



    printf("done\n");
    return 0;
}
