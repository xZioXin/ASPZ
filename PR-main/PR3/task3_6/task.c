#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

void recursive_func(int depth) {
    char data[1024];
    printf("Depth: %d, Address: %p\n", depth, data);
    recursive_func(depth + 1);
}

int main() {
    struct rlimit stack_lim;
    
    stack_lim.rlim_cur = 100;
    stack_lim.rlim_max = 100;
    
    if (setrlimit(RLIMIT_STACK, &stack_lim) != 0) {
        perror("setrlimit failed");
        return 1;
    }
    
    printf("Starting recursion...\n");
    recursive_func(0);
    printf("Recursion completed\n");
    
    return 0;
}