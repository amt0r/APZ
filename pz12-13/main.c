#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void handler(int sig) {
    printf("Received signal: %d (%s)\n", sig, strsignal(sig));
}

int main() {
    sigset_t block_set, wait_set, old_set;

    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);

    sigfillset(&block_set);
    sigprocmask(SIG_SETMASK, &block_set, &old_set);

    printf("All signals blocked temporarily.\n");

    sigfillset(&wait_set);
    sigdelset(&wait_set, SIGUSR1); 

    printf("Waiting for SIGUSR1... (try: `kill -USR1 %d`)\n", getpid());

    sigsuspend(&wait_set);

    printf("Back from sigsuspend\n");

    sigprocmask(SIG_SETMASK, &old_set, NULL);
    printf("Old signal mask restored.\n");

    return 0;
}
