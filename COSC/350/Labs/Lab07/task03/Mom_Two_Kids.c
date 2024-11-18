/* Mom_Two_Kids.c */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int getsize(char*);

int main () {
    char* message;
    int outfd;
    pid_t son_pid;

    son_pid = fork();
    
    switch(son_pid) {
        case -1:
            perror("Error creating child process\n");
            exit(1);
        case 0:
            message = "Hi, Mom";
            umask(0);
            outfd = open("foo", O_WRONLY | O_CREAT | O_TRUNC, 0666);
            break;
        default:
            message = "My son said Hi Mom";
            break;
    }

    if (son_pid == 0) {
        write(outfd, message, getsize(message));
        close(outfd);
        _exit(37);
    } else {
        int status;
        pid_t child_pid;
        child_pid = wait(&status);

        if (WIFEXITED(status)) {
            printf("%s\n", message);
            printf("Child has finished with: PID = %d\n", WEXITSTATUS(status));
        } else
            printf("I have a son?\n");
    }

    return 0;
}

int getsize(char* str) {
    int n = 0;

    while (str[n] != '\0') {
        n++;
    }

    return n;
}

