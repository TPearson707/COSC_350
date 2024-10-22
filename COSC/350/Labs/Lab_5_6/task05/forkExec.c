/* forkExec.c */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int myatoi(char *);

int main(int argc, char *argv[]) {
    
    pid_t pid;
    char *message;
    int n, Nc, Np, Tc, Tp, sleeper, exit_code;
    
    if (argc < 5 || argc > 5) {
        perror("Not enough arguments entered");
        exit(1);
    }
    
    Nc = myatoi(argv[1]);
    Np = myatoi(argv[2]);
    Tc = myatoi(argv[3]);
    Tp = myatoi(argv[4]);

    printf("fork program starting\n");
    pid = vfork();
    switch(pid) {
        case -1:
            perror("vfork failed");
            exit(1);
        case 0:
            execv("child.o", argv);
            _exit(37);
            break;
        default:
            message = "This is the parent";
            n = Np;
            exit_code = 0;
            sleeper = 1;
            break;
    }

    for (; n > 0; n--) {
        printf("Parent: %d\n", getpid());
        sleep(Tp);
    }
    
    if (pid != 0) {
        int stat_val;
        pid_t child_pid;

        child_pid = wait(&stat_val);

        if (WIFEXITED(stat_val))
            printf("Child has finished: PID = %d\n", WEXITSTATUS(stat_val));
        else
            printf("Child terminated abnormally\n");
    }

    exit(exit_code);
}

int myatoi(char *str) {
    int num = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-') {
        sign = -1;
        str++;
    } else if (str[0] == '+') {
        str++;
    }

    while (str[i] != '\0') {
        num = 10 * num + (str[i] - '0');
        i++;
    }

    return num * sign;
}
