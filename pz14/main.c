#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>

#define TIMEOUT 10

timer_t timer_id;
volatile sig_atomic_t stop_server = 0;

void timer_handler(int sig) {
    stop_server = 1;
}

void setup_timer() {
    struct sigevent sev;
    struct itimerspec its;

    memset(&sev, 0, sizeof(sev));
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGALRM;

    timer_create(CLOCK_REALTIME, &sev, &timer_id);

    its.it_value.tv_sec = TIMEOUT;
    its.it_value.tv_nsec = 0;
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 0;

    timer_settime(timer_id, 0, &its, NULL);
}

void reset_idle_timer() {
    struct itimerspec its;

    its.it_value.tv_sec = TIMEOUT;
    its.it_value.tv_nsec = 0;
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 0;

    timer_settime(timer_id, 0, &its, NULL);
}

int main() {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = timer_handler;
    sigaction(SIGALRM, &sa, NULL);

    setup_timer();

    char buffer[256];
    int idle_seconds = 0;

    while (!stop_server) {
        printf("\r>> Waiting for input (%2d/%d seconds): ", idle_seconds, TIMEOUT);
        fflush(stdout);

        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);

        struct timeval timeout = {1, 0};
        int ready = select(STDIN_FILENO + 1, &fds, NULL, NULL, &timeout);

        if (ready > 0 && FD_ISSET(STDIN_FILENO, &fds)) {
            if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                printf("[RECV] You entered: %s", buffer);
                idle_seconds = 0;
                reset_idle_timer();
            }
        } else {
            idle_seconds++;
        }
    }

    printf("\n[INFO] Server shutting down due to inactivity.\n");
    timer_delete(timer_id);
    return 0;
}
