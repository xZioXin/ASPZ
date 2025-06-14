#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    size_t max_size = (size_t)-1 / 2; // 8 EB
    void* ptr = malloc(max_size);
    
    if (ptr == NULL) {
        perror("malloc failed");
        printf("Max allocation failed at %zu bytes (%.2f EB)\n", 
               max_size, (double)max_size/(1024*1024*1024*1024*1024*1024));
    } else {
        printf("Allocated %zu bytes (%.2f EB)\n", 
               max_size, (double)max_size/(1024*1024*1024*1024*1024*1024));
        free(ptr);
    }
    
    return 0;
}