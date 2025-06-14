#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int count = 0;
    pid_t pid;

    while (1) {
        pid = fork();

        if (pid < 0) {
            perror("fork");
            break;
        } else if (pid == 0) {
            _exit(0);
        } else {
            count++;
            printf("Створено процес #%d\n", count);
        }
    }

    printf("Всього створено процесів: %d\n", count);
    return 0;
}