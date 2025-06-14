#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void test_malloc(int xa, int xb) {
    int num = xa * xb;
    size_t size = num;
    
    printf("xa = %d, xb = %d, num = %d, size_t = %zu\n", xa, xb, num, size);
    
    void *ptr = malloc(size);
    if (ptr == NULL) {
        perror("malloc failed");
    } else {
        printf("Successfully allocated %zu bytes\n", size);
        free(ptr);
    }
}

int main() {
    printf("Testing malloc with negative/overflowed values:\n");
    
    test_malloc(10, 20);
    
    test_malloc(INT_MAX/2, 3);
    
    test_malloc(-100, 100);
    
    test_malloc(-100, -100);
    
    return 0;
}