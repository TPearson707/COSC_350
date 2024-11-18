/* pipe3_modified.c */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        printf("Usage: ./pipe3_modified <string>\n");
        exit(1);
    }

    int data_processed;
    int file_pipes[2];
    int size = 0;

    for (int i = 1; i < argc; i++)
        size += strlen(argv[i]) + 1;

    char *buffer = (char *) calloc(size, sizeof(char*));

    for (int i = 1; i < argc; i++) {
        strcat(buffer, argv[i]);
        strcat(buffer, " ");
    }

    pid_t fork_result;

    if (pipe(file_pipes) == 0) {
        fork_result = fork();
        if (fork_result == (pid_t)-1) {
            fprintf(stderr, "Fork failure");
            exit(EXIT_FAILURE);
        }

        if (fork_result == 0) {
            sprintf(buffer, "%d", file_pipes[0]);
            (void)execl("pipe4", "pipe4", buffer, (char *)0);
            
            close(file_pipes[0]);

            exit(EXIT_FAILURE);
        } else {
            data_processed = write(file_pipes[1], buffer, strlen(buffer));
            printf("%d - wrote %d bytes\n", getpid(), data_processed);
            
            close(file_pipes[1]);

            int status;
            waitpid(fork_result, &status, 0);
        }
    }
    exit(EXIT_SUCCESS);
}
