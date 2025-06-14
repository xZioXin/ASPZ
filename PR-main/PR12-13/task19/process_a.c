#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

void sigusr2_handler(int sig) {
    printf("Process A: Received SIGUSR2!\n");
}

int main() {
    signal(SIGUSR2, sigusr2_handler);
    pid_t pid_b = fork();
    
    if (pid_b == 0) {
        execl("./process_b", "process_b", NULL);
    } else {
        // Це процес A
        sleep(1);
        kill(pid_b, SIGUSR1);
        pause();
    }
    return 0;
}