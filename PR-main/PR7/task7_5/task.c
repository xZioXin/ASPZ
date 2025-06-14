#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

void list_files_recursive(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) return;

    struct dirent *entry;
    while ((entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        struct stat statbuf;
        if (stat(full_path, &statbuf) == -1) continue;

        printf("%s\n", full_path);

        if (S_ISDIR(statbuf.st_mode)) {
            list_files_recursive(full_path);
        }
    }

    closedir(dir);
}

int main() {
    list_files_recursive(".");
    return 0;
}