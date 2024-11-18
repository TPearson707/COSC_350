#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void block_signals(sigset_t *set, int sig1, int sig2) {
    sigemptyset(set);
    sigaddset(set, sig1);
    sigaddset(set, sig2);

    if (sigprocmask(SIG_BLOCK, set, 0) == -1) {
        perror("sigprocmask");
        exit(1);
    }
}

void unblock_signal(sigset_t *set, int sig) {
    sigdelset(set, sig);

    if (sigprocmask(SIG_SETMASK, set, 0) == -1) {
        perror("sigprocmask");
        exit(1);
    }
}

int main() {
    sigset_t signal_set;

    printf("Starting first loop (SIGINT and SIGQUIT blocked)\n");

    block_signals(&signal_set, SIGINT, SIGQUIT);
    for (int i = 1; i <= 5; i++) {
        printf("%d\n", i);
        sleep(1);
    }

    printf("Starting second loop (only SIGINT blocked)\n");

    unblock_signal(&signal_set, SIGQUIT);
    for (int i = 0; i <= 5; i++) {
        printf("%d\n", i);
        sleep(1);
    }
    
    sigprocmask(SIG_UNBLOCK, &signal_set, 0);

    printf("Done\n");
    return 0;
}
