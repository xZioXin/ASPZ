#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_random_numbers(double n) {
    srand(time(NULL) ^ (unsigned long)&generate_random_numbers);

    printf("Random numbers 0.0-1.0:\n");
    for (int i = 0; i < 5; i++) {
        printf("%.6f\n", (double)rand() / RAND_MAX);
    }

    printf("\nRandom numbers 0.0-%.1f:\n", n);
    for (int i = 0; i < 5; i++) {
        printf("%.6f\n", (double)rand() / RAND_MAX * n);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return 1;
    }

    double n = atof(argv[1]);
    if (n <= 0) {
        fprintf(stderr, "n must be positive\n");
        return 1;
    }

    generate_random_numbers(n);
    return 0;
}