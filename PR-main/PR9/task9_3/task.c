#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    FILE *f = fopen("test_file.txt", "w");
    if (!f) {
        perror("Помилка створення файлу");
        return 1;
    }
    fprintf(f, "Початковий вміст\n");
    fclose(f);

    printf("Копіювання файлу під root...\n");
    system("sudo cp test_file.txt ~/test_file_root_copy.txt");
    system("sudo chown root:root ~/test_file_root_copy.txt");

    printf("\nСпроба змінити файл:\n");
    f = fopen("~/test_file_root_copy.txt", "a");
    if (!f) {
        perror("Помилка відкриття для запису");
    } else {
        fprintf(f, "Новий вміст\n");
        fclose(f);
    }

    printf("\nСпроба видалити файл:\n");
    if (remove("~/test_file_root_copy.txt") == -1) {
        perror("Помилка видалення");
    }

    return 0;
}