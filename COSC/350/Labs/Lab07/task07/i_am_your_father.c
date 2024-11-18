/* i_am_your_father.c use the force luke */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    
    int ogppid = 0;
    int i = 990;
    char* message;
    pid_t pid;
    
    pid = fork();

    switch(pid) {
        case -1:
            perror("Error creating child process\n");
            exit(1);
        case 0:
            ogppid = getppid();
            printf("child process starting\n");
            message = "I am your child.";
            break;
        default:
            printf("parent process starting\n");
            message = "This is the parent";
            break;
    }
    
        if (pid == 0) {
            while (ogppid != getppid()) {
                printf("I am your child.\n");
                sleep(1);
            }
            
            printf("Since my parent has completed its job, I am done too\n");
            exit(0);

        } else {
            for (int i = 0; i < 1000; i++) {
                printf("I am your parent\n");
            }

            printf("My job is done\n");
            exit(0);
         } 
    return 0;
}
