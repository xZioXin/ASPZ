#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    DIR *dir = opendir(".");
    if (!dir) {
        perror("opendir failed");
        return 1;
    }

    char *subdirs[1000];
    int count = 0;

    struct dirent *entry;
    struct stat statbuf;
    
    while ((entry = readdir(dir)) && count < 1000) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        if (stat(entry->d_name, &statbuf) == -1) {
            continue;
        }

        if (S_ISDIR(statbuf.st_mode)) {
            subdirs[count] = strdup(entry->d_name);
            if (subdirs[count] == NULL) {
                perror("strdup failed");
                break;
            }
            count++;
        }
    }
    closedir(dir);

    qsort(subdirs, count, sizeof(char *), compare_strings);

    for (int i = 0; i < count; i++) {
        printf("%s\n", subdirs[i]);
        free(subdirs[i]);
    }

    return 0;
}