#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

int main() {
    DIR *dir = opendir(".");
    if (!dir) {
        perror("opendir failed");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        printf("Delete %s? (y/n/q): ", entry->d_name);
        int c = getchar();
        while (getchar() != '\n');

        if (c == 'y' || c == 'Y') {
            if (unlink(entry->d_name) == 0) {
                printf("Deleted %s\n", entry->d_name);
            } else {
                perror("unlink failed");
            }
        } else if (c == 'q' || c == 'Q') {
            break;
        }
    }

    closedir(dir);
    return 0;
}