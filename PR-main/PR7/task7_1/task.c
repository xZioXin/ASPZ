#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *pipe;
    char buffer[1024];

    pipe = popen("rwho | more", "r");
    if (pipe == NULL) {
        perror("Помилка при відкритті каналу");
        return EXIT_FAILURE;
    }

    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        printf("%s", buffer);
    }

    if (pclose(pipe) == -1) {
        perror("Помилка при закритті каналу");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}