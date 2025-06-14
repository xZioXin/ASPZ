#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

void test_directory(const char *path) {
    printf("\nАналіз каталогу %s:\n", path);
    system("ls -l");

    DIR *dir = opendir(path);
    if (!dir) {
        perror("Помилка відкриття каталогу");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir))) {
        if (entry->d_name[0] == '.') continue;

        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(fullpath, &st) == -1) continue;

        printf("\nФайл: %s\n", entry->d_name);
        printf("Власник: %d, Група: %d\n", st.st_uid, st.st_gid);
        printf("Права: %o\n", st.st_mode & 0777);

        printf("Доступ: Читання=%s, Запис=%s, Виконання=%s\n",
               access(fullpath, R_OK) ? "Ні" : "Так",
               access(fullpath, W_OK) ? "Ні" : "Так",
               access(fullpath, X_OK) ? "Ні" : "Так");
    }

    closedir(dir);
}

int main() {
    test_directory(getenv("HOME"));
    test_directory("/usr/bin");
    test_directory("/etc");
    
    return 0;
}