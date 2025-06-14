#include <stdio.h>
#include <stdlib.h>

struct sbar {
    int a;
    double b;
};

void test_realloc() {
    struct sbar *ptr = calloc(1000, sizeof(struct sbar));
    if (!ptr) {
        perror("calloc");
        return;
    }
    printf("calloc allocated: %p\n", (void*)ptr);

    struct sbar *newptr = realloc(ptr, 500 * sizeof(struct sbar));
    if (!newptr) {
        perror("realloc");
        free(ptr);
        return;
    }
    printf("realloc resized to 500 elements: %p\n", (void*)newptr);

    free(newptr);
}

void test_reallocarray() {
    struct sbar *ptr = calloc(1000, sizeof(struct sbar));
    if (!ptr) {
        perror("calloc");
        return;
    }
    printf("calloc allocated: %p\n", (void*)ptr);

    struct sbar *newptr = reallocarray(ptr, 500, sizeof(struct sbar));
    if (!newptr) {
        perror("reallocarray");
        free(ptr);
        return;
    }
    printf("reallocarray resized to 500 elements: %p\n", (void*)newptr);

    free(newptr);
}

int main() {
    // test_realloc();
    test_reallocarray();
    return 0;
}