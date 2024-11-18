#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void parent_response1(int sig) {
    printf("Hi Honey! Anything wrong?\n");
}

void parent_response2(int sig) {
    printf("Do you make trouble again?\n");
}

int main() {
    pid_t child1, child2;

    struct sigaction sa1, sa2;

    sa1.sa_handler = parent_response1;
    sigemptyset(&sa1.sa_mask);
    sa1.sa_flags = 0;
    sigaction(SIGUSR1, &sa1, 0);

    sa2.sa_handler = parent_response2;
    sigemptyset(&sa2.sa_mask);
    sa2.sa_flags = 0;
    sigaction(SIGUSR2, &sa2, 0);

    if ((child1 = fork()) == 0) {
        sleep(1);
        kill(getppid(), SIGUSR1);
        _exit(0);
    }

    if ((child2 = fork()) == 0) {
        sleep(2);
        kill(getppid(), SIGUSR2);
        _exit(0);
    }

    waitpid(child1, NULL, 0);
    waitpid(child2, NULL, 0);

    return 0;
}
