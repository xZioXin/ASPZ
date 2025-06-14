#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <time.h>
#include <unistd.h>

void measure_time() {
    struct timespec start, end;
    
    if (clock_gettime(CLOCK_MONOTONIC, &start) == -1) {
        perror("clock_gettime");
        return;
    }

    for (volatile int i = 0; i < 1000000; i++);

    if (clock_gettime(CLOCK_MONOTONIC, &end) == -1) {
        perror("clock_gettime");
        return;
    }

    long elapsed_ns = (end.tv_sec - start.tv_sec) * 1000000000L + 
                     (end.tv_nsec - start.tv_nsec);
    double elapsed_ms = elapsed_ns / 1000000.0;

    printf("Execution time: %.3f ms\n", elapsed_ms);
}

int main() {
    measure_time();
    return 0;
}