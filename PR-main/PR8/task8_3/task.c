#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

void test_qsort(int *arr, int n, const char *desc) {
    clock_t start = clock();
    qsort(arr, n, sizeof(int), cmp);
    double time = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("%s: %.5f сек\n", desc, time);
}

int main() {
    const int n = 100000;
    int *arr1 = malloc(n * sizeof(int));
    int *arr2 = malloc(n * sizeof(int));
    int *arr3 = malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        arr1[i] = i;
        arr2[i] = 42;
        arr3[i] = n - i;
    }

    test_qsort(arr1, n, "Відсортований масив");
    test_qsort(arr2, n, "Однакові елементи");
    test_qsort(arr3, n, "Зворотньо відсортований");

    free(arr1); free(arr2); free(arr3);
    return 0;
}