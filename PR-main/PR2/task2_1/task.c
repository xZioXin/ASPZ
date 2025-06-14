#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <stdint.h>

int main() {
    printf("Розмір time_t: %zu байт\n", sizeof(time_t));

    time_t max_time = (time_t)((1ULL << (sizeof(time_t)*8 - 1)) - 1);
    printf("Максимальне значення time_t: %lld\n", (long long)max_time);

    char* time_str = ctime(&max_time);
    if (time_str)
        printf("Дата максимального time_t: %s", time_str);
    else
        perror("Помилка при перетворенні часу");

    return 0;
}