#include <unistd.h>
#include <stdio.h>

int main() {
    int pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return 1;
    }
    printf("%d\n", pid);
    return 0;
}