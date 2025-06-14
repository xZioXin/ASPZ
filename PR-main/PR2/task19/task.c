#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Використання: %s <elf-файл>\n", argv[0]);
        return 1;
    }

    char command[512];
    snprintf(command, sizeof(command), "ldd %s", argv[1]);

    int ret = system(command);
    if (ret == -1) {
        perror("Не вдалося виконати команду");
        return 1;
    }

    return 0;
}