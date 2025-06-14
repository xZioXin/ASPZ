#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int global_v = 42;

void dummy_function() {}

int main() {
    int local_var = 1;

    printf("=== Початкове розташування ===\n");
    printf("Stack top (local variable)    : %p\n", (void *)&local_var);
    printf("Data segment   : %p\n", (void *)&global_v);
    printf("Text segment (function addr)  : %p\n", (void *)&dummy_function);

    char big_stack_array[1024 * 1024];
    strcpy(big_stack_array, "test");
    printf("\n=== Після створення великого масиву ===\n");
    printf("Stack top (big array)         : %p\n", (void *)big_stack_array);

    return 0;
}

