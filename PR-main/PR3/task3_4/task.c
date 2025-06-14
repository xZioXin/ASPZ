#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>

#define MAX_CPU_TIME 2
#define MAIN_NUMBERS 7
#define MAIN_RANGE 49
#define BONUS_NUMBERS 6
#define BONUS_RANGE 36

volatile sig_atomic_t time_limit_exceeded = false;

void handle_alarm(int sig) {
    time_limit_exceeded = true;
}

void generate_unique_numbers(int *array, int count, int range) {
    bool used[range + 1];
    for (int i = 0; i <= range; i++) used[i] = false;

    for (int i = 0; i < count; ) {
        int num = rand() % range + 1;
        if (!used[num]) {
            used[num] = true;
            array[i] = num;
            i++;
        }
    }
}

void sort_numbers(int *array, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void print_numbers(const char *label, int *numbers, int count) {
    printf("%s: ", label);
    for (int i = 0; i < count; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
}

int main() {
    signal(SIGALRM, handle_alarm);
    alarm(MAX_CPU_TIME);

    srand(time(NULL));

    int main_numbers[MAIN_NUMBERS];
    int bonus_numbers[BONUS_NUMBERS];

    generate_unique_numbers(main_numbers, MAIN_NUMBERS, MAIN_RANGE);
    generate_unique_numbers(bonus_numbers, BONUS_NUMBERS, BONUS_RANGE);

    if (time_limit_exceeded) {
        printf("Попередження: Ліміт часу CPU майже вичерпано!\n");
    }

    sort_numbers(main_numbers, MAIN_NUMBERS);
    sort_numbers(bonus_numbers, BONUS_NUMBERS);

    print_numbers("Основні числа (7 з 49)", main_numbers, MAIN_NUMBERS);
    print_numbers("Бонусні числа (6 з 36)", bonus_numbers, BONUS_NUMBERS);

    return 0;
}