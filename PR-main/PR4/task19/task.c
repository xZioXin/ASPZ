#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>

#define CHUNK_SIZE (1024 * 1024 * 100)

int main() {
    struct rlimit mem_limit;
    mem_limit.rlim_cur = RLIM_INFINITY;
    mem_limit.rlim_max = RLIM_INFINITY;
    setrlimit(RLIMIT_AS, &mem_limit);

    int i = 0;
    while (1) {
        char *mem = malloc(CHUNK_SIZE);
        if (mem == NULL) {
            perror("malloc failed");
            break;
        }
        for (size_t j = 0; j < CHUNK_SIZE; j += 4096) {
            mem[j] = 0;
        }
        printf("Allocated %d MB\n", ++i * 100);
    }

    return 0;
}