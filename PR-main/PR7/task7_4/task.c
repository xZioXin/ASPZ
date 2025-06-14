#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

void pause_output() {
    printf("--Press ENTER to continue--");
    while (getchar() != '\n');
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s file...\n", argv[0]);
        return 1;
    }

    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (!file) {
            perror(argv[i]);
            continue;
        }

        char line[1024];
        int line_count = 0;
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
            if (++line_count % 20 == 0) {
                pause_output();
            }
        }

        fclose(file);
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return 0;
}