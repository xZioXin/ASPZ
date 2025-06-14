#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <pthread.h>
#include <time.h>

#define MAX_THREADS 100
#define MAX_CPU_TIME 5
#define MAX_MEMORY (256 * 1024 * 1024)

void* worker_thread(void* arg) {
    int id = *(int*)arg;
    printf("Thread %d started\n", id);
    
    volatile double calc = 0;
    for (long i = 0; i < 100000000; i++) {
        calc += 1.0 / (i + 1);
        if (i % 1000000 == 0) {
            printf("Thread %d working...\n", id);
        }
    }
    
    printf("Thread %d finished (result=%.2f)\n", id, calc);
    return NULL;
}

void set_limits() {
    struct rlimit cpu_lim, mem_lim;
    
    cpu_lim.rlim_cur = MAX_CPU_TIME;
    cpu_lim.rlim_max = MAX_CPU_TIME;
    setrlimit(RLIMIT_CPU, &cpu_lim);
    
    mem_lim.rlim_cur = MAX_MEMORY;
    mem_lim.rlim_max = MAX_MEMORY;
    setrlimit(RLIMIT_AS, &mem_lim);
}

int main() {
    set_limits();
    
    pthread_t threads[MAX_THREADS];
    int thread_ids[MAX_THREADS];
    time_t start = time(NULL);
    
    printf("Starting load test (PID: %d)\n", getpid());
    printf("Max CPU time: %d sec\n", MAX_CPU_TIME);
    printf("Max memory: %d MB\n", MAX_MEMORY/(1024*1024));
    
    for (int i = 0; i < MAX_THREADS; i++) {
        thread_ids[i] = i;
        if (pthread_create(&threads[i], NULL, worker_thread, &thread_ids[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }
    
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("Test completed in %ld seconds\n", time(NULL) - start);
    return 0;
}