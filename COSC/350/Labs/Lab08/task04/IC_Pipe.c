/* IC_Pipe.c */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 256

int sum(int, int);
void err_sys(char *);

int main(int argc, char *argv[]) {
    int n, fd[2], size, a, b;
    pid_t pid;
    char sline[MAXLINE], rline[MAXLINE];

    if (pipe(fd) < 0) // create a pipe
        err_sys("pipe error");

    if ( (pid = fork()) < 0) // create child
        err_sys("fork error");

    else if (pid > 0) {// parent uses the pipe to send a message to child
        close(fd[0]); // fd[1] used for sending data
        printf("Submit two integers\n");
        while ( (size = read(STDIN_FILENO, sline, MAXLINE)) > 0) {
            write(fd[1], sline, size); // write to pipe
            printf("Submit two integers\n");
        }

        close(fd[1]);
    }
    else {// child uses pipe to receive message from parent
        close(fd[1]);

        while ((n = read(fd[0], rline, MAXLINE)) > 0) { // read from pipe
            // chose first two string as two integer
            if (sscanf(rline, "%d%d", &a, &b) == 2) {
                sprintf(rline, "%d\n", sum(a, b));
                n = strlen(rline);

                if (write(STDOUT_FILENO, rline, n) != n)
                    err_sys("Write Error");
            } else {
                if (write(STDOUT_FILENO, "invalid args\n", 13) != 13)
                    err_sys("write error");
            }
        }
        
        close(fd[0]);
    }

    return 0;
}

int sum(int a, int b) {
    return a + b;
}

void err_sys(char *str) {
    printf("%s\n");
    exit(1);
}


