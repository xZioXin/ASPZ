#include <stdio.h>
#include <stdlib.h>

void test_malloc_zero() {
    printf("Testing malloc(0):\n");
    
    void *ptr = malloc(0);
    printf("malloc(0) returned %p\n", ptr);
    
    if (ptr != NULL) {
        printf("Pointer is not NULL, trying to free it...\n");
        free(ptr);
        printf("free() succeeded\n");
    } else {
        printf("Got NULL pointer\n");
    }
}

int main() {
    test_malloc_zero();
    return 0;
}