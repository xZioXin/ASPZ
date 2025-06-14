#include <stdio.h>

int *get_ptr() {
    int local = 42;
    return &local;
}

int main() {
    int *ptr = get_ptr();
    printf("*ptr = %d\n", *ptr);
    return 0;
}