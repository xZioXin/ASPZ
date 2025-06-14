#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

void print_permissions(mode_t mode) {
    printf((S_ISDIR(mode)) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}

int main() {
    DIR *dir = opendir(".");
    if (!dir) {
        perror("opendir failed");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir))) {
        struct stat file_stat;
        if (stat(entry->d_name, &file_stat) == -1) continue;

        print_permissions(file_stat.st_mode);
        printf(" %2lu", file_stat.st_nlink);

        struct passwd *pw = getpwuid(file_stat.st_uid);
        struct group *gr = getgrgid(file_stat.st_gid);
        printf(" %8s %8s", pw ? pw->pw_name : "?", gr ? gr->gr_name : "?");

        printf(" %8ld", file_stat.st_size);

        char time_buf[20];
        strftime(time_buf, 20, "%b %d %H:%M", localtime(&file_stat.st_mtime));
        printf(" %s %s\n", time_buf, entry->d_name);
    }

    closedir(dir);
    return 0;
}