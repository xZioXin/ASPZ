#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

void test_access(const char *filename) {
    printf("\nТестування доступу до %s:\n", filename);
    printf("Читання: %s\n", access(filename, R_OK) ? "Заборонено" : "Дозволено");
    printf("Запис: %s\n", access(filename, W_OK) ? "Заборонено" : "Дозволено");
    printf("Виконання: %s\n", access(filename, X_OK) ? "Заборонено" : "Дозволено");
}

int main() {
    const char *filename = "test.txt";
    
    FILE *f = fopen(filename, "w");
    fprintf(f, "Тестовий файл\n");
    fclose(f);

    test_access(filename);

    printf("\nЗміна прав через sudo...\n");
    char cmd[100];
    snprintf(cmd, sizeof(cmd), "sudo chown root:root %s", filename);
    system(cmd);
    snprintf(cmd, sizeof(cmd), "sudo chmod 600 %s", filename);
    system(cmd);

    test_access(filename);

    snprintf(cmd, sizeof(cmd), "sudo chown %d:%d %s", getuid(), getgid(), filename);
    system(cmd);
    chmod(filename, 0644);

    remove(filename);
    return 0;
}