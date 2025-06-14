#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

void sigusr1_handler(int sig) {
    printf("Process B: Received SIGUSR1, sending SIGUSR2!\n");
    kill(getppid(), SIGUSR2);
}

int main() {
    signal(SIGUSR1, sigusr1_handler);
    while (1) pause();
    return 0;
}