#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>
#include <ctype.h>
#include <linux/limits.h>


#define PROC_DIR "/proc"
#define MAX_PROCESSES 32768

typedef struct {
    char path[PATH_MAX];
    int pids[MAX_PROCESSES];
    int count;
} FileUsage;

FileUsage files[10000];
int fileCount = 0;

int is_numeric(const char *s) {
    while (*s) {
        if (!isdigit(*s++)) return 0;
    }
    return 1;
}

void add_file_usage(const char *file, int pid) {
    for (int i = 0; i < fileCount; ++i) {
        if (strcmp(files[i].path, file) == 0) {
            files[i].pids[files[i].count++] = pid;
            return;
        }
    }
    // New file
    strcpy(files[fileCount].path, file);
    files[fileCount].pids[0] = pid;
    files[fileCount].count = 1;
    fileCount++;
}

void scan_process_fds() {
    struct dirent *entry;
    DIR *proc = opendir(PROC_DIR);
    if (!proc) {
        perror("opendir /proc");
        exit(1);
    }

    while ((entry = readdir(proc)) != NULL) {
        if (!is_numeric(entry->d_name)) continue;

        int pid = atoi(entry->d_name);
        char fd_path[PATH_MAX];
        snprintf(fd_path, sizeof(fd_path), PROC_DIR"/%d/fd", pid);

        DIR *fd_dir = opendir(fd_path);
        if (!fd_dir) continue;

        struct dirent *fd_entry;
        while ((fd_entry = readdir(fd_dir)) != NULL) {
            if (!is_numeric(fd_entry->d_name)) continue;

            char link_path[PATH_MAX];
            char target_path[PATH_MAX];
            snprintf(link_path, sizeof(link_path), "%s/%s", fd_path, fd_entry->d_name);
            ssize_t len = readlink(link_path, target_path, sizeof(target_path) - 1);
            if (len > 0) {
                target_path[len] = '\0';
                if (target_path[0] == '/') {  // skip special files like 'anon_inode'
                    add_file_usage(target_path, pid);
                }
            }
        }
        closedir(fd_dir);
    }

    closedir(proc);
}

void print_shared_usages() {
    printf("Shared file dependencies detected:\n\n");
    for (int i = 0; i < fileCount; ++i) {
        if (files[i].count > 1) {
            printf("File: %s\n  Used by PIDs:", files[i].path);
            for (int j = 0; j < files[i].count; ++j) {
                printf(" %d", files[i].pids[j]);
            }
            printf("\n\n");
        }
    }
}

int main() {
    scan_process_fds();
    print_shared_usages();
    return 0;
}