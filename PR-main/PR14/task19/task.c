#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

volatile sig_atomic_t signal_count = 0;
volatile sig_atomic_t overrun_count = 0;
volatile sig_atomic_t keep_running = 1;

void timer_handler(int sig, siginfo_t *si, void *uc) {
    signal_count++;

    int overrun = si->si_overrun;
    if (overrun > 0) {
        overrun_count += overrun;
        printf("Пропущено тики: %d (всього: %d)\n", overrun, overrun_count);
    }

    usleep(20000);
}

void sigint_handler(int sig) {
    keep_running = 0;
}

int main() {
    struct sigaction sa;
    struct sigevent sev;
    timer_t timerid;
    struct itimerspec its;
    int sig = SIGRTMIN;

    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = timer_handler;
    sigemptyset(&sa.sa_mask);
    if (sigaction(sig, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // Handle SIGINT (Ctrl+C)
    struct sigaction sa_int;
    sa_int.sa_handler = sigint_handler;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    if (sigaction(SIGINT, &sa_int, NULL) == -1) {
        perror("sigaction(SIGINT)");
        exit(EXIT_FAILURE);
    }

    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = sig;
    sev.sigev_value.sival_ptr = &timerid;
    if (timer_create(CLOCK_REALTIME, &sev, &timerid) == -1) {
        perror("timer_create");
        exit(EXIT_FAILURE);
    }

    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = 10000000;
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 10000000;

    if (timer_settime(timerid, 0, &its, NULL) == -1) {
        perror("timer_settime");
        exit(EXIT_FAILURE);
    }

    printf("Таймер стартував. Очікуємо сигнали... (Натисніть Ctrl+C для зупинки)\n");

    while (keep_running) {
        pause();
    }

    printf("\nПідсумок:\n");
    printf("Отримано сигналів: %d\n", signal_count);
    printf("Втрачено тика (si_overrun): %d\n", overrun_count);

    return 0;
}