#include <stdio.h>
#include <stdlib.h>

#define CYCLES 3

void incorrect_usage(size_t n) {
    printf("\nIncorrect_usage:\n");
    void *ptr = NULL;

    for (int i = 0; i < CYCLES; i++) {
        if (!ptr)
            ptr = malloc(n);  

        if (!ptr) {
            printf("malloc failed on iteration %d\n", i);
            return;
        }

        printf("malloc -> %p on iteration %d\n", ptr, i);

        free(ptr);    
    }
}

void correct_usage(size_t n) {
    printf("\nCorrect_usage:\n");
    void *ptr = malloc(n);

    if (!ptr) {
        printf("malloc failed\n");
        return;
    }

    for (int i = 0; i < CYCLES; i++) {
        printf("Using the same ptr -> %p on iteration %d\n", ptr, i);
    }

    free(ptr);  
}

int main() {
    size_t n = 32;

    correct_usage(n);
    incorrect_usage(n);  

    return 0;
}