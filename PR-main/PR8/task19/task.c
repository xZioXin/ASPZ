#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    const char *filename = "test.txt";
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    if (fd == -1) {
        perror("open failed");
        return 1;
    }

    char buffer[1024 * 1024];
    memset(buffer, 'A', sizeof(buffer));

    ssize_t written;
    while ((written = write(fd, buffer, sizeof(buffer)))) {
        if (written == -1) {
            perror("write failed");
            printf("errno: %d (%s)\n", errno, strerror(errno));
            break;
        }
        printf("Written: %zd bytes\n", written);
    }

    close(fd);
    return 0;
}