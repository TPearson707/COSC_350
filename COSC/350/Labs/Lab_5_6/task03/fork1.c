/* fork.c page 474 */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int myatoi(char *);

int main(int argc, char *argv[]) {
    
    pid_t pid;
    char *message;
    int n, Nc, Np, Tc, Tp, sleeper;
    
    if (argc < 5 || argc > 5) {
        perror("Not enough arguments entered");
        exit(1);
    }
    
    Nc = myatoi(argv[1]);
    Np = myatoi(argv[2]);
    Tc = myatoi(argv[3]);
    Tp = myatoi(argv[4]);

    printf("fork program starting\n");
    pid = fork();
    switch(pid) {
        case -1:
            perror("fork failed");
            exit(1);
        case 0:
            message = "This is a child";
            n = Nc;
            sleeper = 0;
            break;
        default:
            message = "This is the parent";
            n = Np;
            sleeper = 1;
            break;
    }

    for (; n > 0; n--) {
        puts(message);
        if (sleeper == 0)
            sleep(Tc);
        else
            sleep(Tp);
    }

    exit(0);
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
