#include "threads.h"

int main() {
    RingBuffer *ringBuffer = buffer_init();
    printf("%p\n", (void *)ringBuffer);
    printf("empty: %d, full: %d\n", buffer_is_empty(ringBuffer), buffer_is_full(ringBuffer));
    Stats *stats;
    printf("buffer: %lu, stats: %lu\n", sizeof(*ringBuffer), sizeof(*stats));
    return 0;
}
