#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <unistd.h>

bool is_c_file(const char *filename) {
    const char *dot = strrchr(filename, '.');
    return dot && strcmp(dot, ".c") == 0;
}

int main() {
    DIR *dir = opendir(".");
    if (!dir) {
        perror("opendir failed");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir))) {
        if (is_c_file(entry->d_name)) {
            printf("%s\n", entry->d_name);
        }
    }
    rewinddir(dir);

    printf("\nGrant read permission to others? (y/n): ");
    int c = getchar();
    if (c == 'y' || c == 'Y') {
        while ((entry = readdir(dir))) {
            if (is_c_file(entry->d_name)) {
                struct stat st;
                if (stat(entry->d_name, &st) == 0) {
                    mode_t new_mode = st.st_mode | S_IROTH;
                    if (chmod(entry->d_name, new_mode) == 0) {
                        printf("Added read permission for %s\n", entry->d_name);
                    }
                }
            }
        }
    }

    closedir(dir);
    return 0;
}