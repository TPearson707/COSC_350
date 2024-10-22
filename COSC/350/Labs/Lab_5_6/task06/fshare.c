/* fshare.c */

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#define BUFFER_SIZE 1

static int alarm_fired = 0;

void ding(int);
int checkNumeric(char);

int main(int argc, char *argv[]) {

    pid_t pid;
    int infd, outfd, nbyte;
    char buffer[BUFFER_SIZE];
    
    signal(SIGALRM, ding);

    if (argc < 2 || argc > 2) {
        perror("Invalid number of arguments");
        exit(1);
    }

    infd = open(argv[1], O_RDONLY);

    if (infd < 0) {
        perror("Error opening message.txt");
        exit(1);
    }

    pid = fork();

    switch(pid) {
        case -1:
            perror("Erorr creating child process");
            exit(1);
    }
    
    if (pid == 0) {

        outfd = open("child.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);

        if (outfd < 0) {
            perror("Error opening child.txt");
            exit(1);
        }

        while ((nbyte = read(infd, buffer, BUFFER_SIZE)) > 0) {
            printf("child: %s\n", buffer); 
            if (checkNumeric(buffer[0]) == 0) {
                if (write(outfd, buffer, nbyte) != nbyte) {
                    perror("Error writing to child.txt");
                    close(infd);
                    close(outfd);
                    exit(1);
                }
            }
        }
        close(outfd);
        kill(getppid(), SIGALRM);
        exit(0);

    } else {
        
        while (!alarm_fired) {
            pause();
        }
        
        if (lseek(infd, 0, SEEK_SET) < 0) {
            perror("Error using lseek");
            exit(1);
        }

        outfd = open("parent.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);

        if (outfd < 0) {
            perror("Error opening parent.txt");
            exit(1);
        }

        while ((nbyte = read(infd, buffer, BUFFER_SIZE)) > 0) {
            printf("parent: %s\n", buffer);
            if (checkNumeric(buffer[0])) {
                if (write(outfd, buffer, nbyte) != nbyte) {
                    perror("Error writing to parent");
                    close(infd);
                    close(outfd);
                    exit(1);
                }
            }
        }
            
    }
    
    close(infd);
    close(outfd);

    return 0;
}

void ding(int sig) {
    alarm_fired = 1;
}

int checkNumeric(char c) {
    if (c <= '9' && c >='0')
        return 1;

    return 0;

}
