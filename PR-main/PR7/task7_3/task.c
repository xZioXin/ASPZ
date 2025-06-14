#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void search_in_file(FILE *file, const char *filename, const char *pattern) {
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, pattern)) {
            printf("%s: %s", filename, line);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s pattern [file...]\n", argv[0]);
        return 1;
    }

    const char *pattern = argv[1];

    if (argc == 2) {
        search_in_file(stdin, "stdin", pattern);
    } else {
        for (int i = 2; i < argc; i++) {
            FILE *file = fopen(argv[i], "r");
            if (!file) {
                perror(argv[i]);
                continue;
            }
            search_in_file(file, argv[i], pattern);
            fclose(file);
        }
    }

    return 0;
}