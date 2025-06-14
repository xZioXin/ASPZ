#include <stdio.h>
#include <stdlib.h>

void test_realloc_edge_cases() {
    printf("=== Testing realloc with NULL pointer ===\n");
    
    void *ptr1 = realloc(NULL, 100);
    if (ptr1) {
        printf("realloc(NULL, 100) succeeded: %p\n", ptr1);
        free(ptr1);
    } else {
        perror("realloc(NULL, 100) failed");
    }

    printf("\n=== Testing realloc with size 0 ===\n");
    
    void *ptr2 = malloc(50);
    printf("Allocated ptr: %p\n", ptr2);
    
    void *ptr3 = realloc(ptr2, 0);
    printf("After realloc(ptr, 0): %p\n", ptr3);
    
    if (ptr3) {
        printf("Note: got non-NULL from realloc(ptr, 0)\n");
        free(ptr3);
    }
}

int main() {
    test_realloc_edge_cases();
    return 0;
}