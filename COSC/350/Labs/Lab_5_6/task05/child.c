/* child.c */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int myatoi(char *);

int main(int argc, char *argv[]) {
    pid_t pid;
    char *message;
    int n, Nc, Tc, sleeper, exit_code;

    Nc = myatoi(argv[1]);
    Tc = myatoi(argv[3]);

    
}

int myatoi(char *str) {
    int num = 0;
    int sign = 1;

    if (str[0] == '-') {
        sign = -1;
        str++;
    } else if (str[0] == '+')
        str++;

    while (str[i] != '\0') {
        num = 10 * num + (str[i] - '0');
        i++
    }

    return num * sign;
}
