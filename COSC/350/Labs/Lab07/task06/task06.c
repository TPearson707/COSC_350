#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void terminate_parent(int sig) {
    printf("Parent received SIGUSR2, now terminating\n");
    exit(0);
}

void terminate_child(int sig) {
    printf("Child received SIGUSR1, now terminating\n");
    kill(getppid(), SIGUSR2); // Send SIGUSR2 to parent
    _exit(0);
}

int main() {
    pid_t child, grandchild;
    struct sigaction sa;

    child = fork();
    if (child == -1) {
        perror("Failed to fork child");
        exit(1);
    }

    if (child == 0) {  // Child process
        sa.sa_handler = terminate_child;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        sigaction(SIGUSR1, &sa, 0);

        grandchild = fork();
        if (grandchild == -1) {
            perror("Failed to fork grandchild");
            exit(1);
        }

        if (grandchild == 0) {  // Grandchild process
            int print_count = 0;
            while (1) {
                printf("Grandchild process\n");
                print_count++;

                if (print_count == 10) {
                    kill(getppid(), SIGUSR1);  // Send SIGUSR1 to child
                }

                // Check if parent is terminated
                if (getppid() == 1) {
                    printf("Grandchild detected parent has terminated, exiting now.\n");
                    _exit(0);
                }
            }
        } else {  // Child process
            while (1) {
                printf("Child process\n");
            }
        }

    } else {  // Parent process
        sa.sa_handler = terminate_parent;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        sigaction(SIGUSR2, &sa, 0);

        while (1) {
            printf("Parent process\n");
        }
    }

    return 0;
}

