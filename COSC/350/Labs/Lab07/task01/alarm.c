/* alarm.c */
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int alarm_fired = 0;

// signal handler for SIGALRM
void ding(int sig) {
    alarm_fired = 1;
}

int main() {
    pid_t pid; 

    printf("alarm application starting\n");

    pid = fork();
    switch (pid) {
        case -1: /* failure */
            perror("fork failed");
            exit(1);
        case 0: /* child */
            sleep(5);
            kill(getppid(), SIGALRM);
            _exit(0);
    }
    
    /* if we get here we are the parent process */
    printf ("Waiting for alarm to go off\n");
    signal (SIGALRM, ding);
    pause();
    if (alarm_fired)
        printf("Ding!\n");
    
    printf("done\n");
    exit(0);
