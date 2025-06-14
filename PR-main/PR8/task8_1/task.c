#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    int fd = open("test.txt", O_WRONLY|O_CREAT, 0644);
    char buf[1024] = {0};
    
    ftruncate(fd, 512);
    
    ssize_t count = write(fd, buf, sizeof(buf));
    printf("Записано %zd з %zu байт\n", count, sizeof(buf));
    
    close(fd);
    return 0;
}