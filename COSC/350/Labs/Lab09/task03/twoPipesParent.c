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
    int file_pipes[2]; // parent -> child
    int file_pipes2[2]; // child -> parent
    int size = 0;

    for (int i = 1; i < argc; i++)
        size += strlen(argv[i]) + 1;

    char *buffer = (char *) calloc(size, sizeof(char*));
    char *buffer2 = (char *) calloc(size, sizeof(char*));

    for (int i = 1; i < argc; i++) {
        strcat(buffer, argv[i]);
        strcat(buffer, " ");
    }

    pid_t fork_result;

    if (pipe(file_pipes) == 0 && pipe(file_pipes2) == 0) {
        fork_result = fork();
        if (fork_result == (pid_t)-1) {
            fprintf(stderr, "Fork failure");
            exit(EXIT_FAILURE);
        }

        if (fork_result == 0) {
            close(file_pipes[1]); // write parent -> child
            close(file_pipes2[0]); // read child -> parent

            sprintf(buffer, "%d", file_pipes[0]);
            sprintf(buffer2, "%d", file_pipes2[1]);
            (void)execl("./twoPipesChild", "twoPipesChild", buffer, buffer2, (char *)0);
            
            close(file_pipes[0]); // read parent -> child
            close(file_pipes2[1]); // write child -> parent

            exit(EXIT_FAILURE);
        } else {
            close(file_pipes[0]); // read parent -> child
            close(file_pipes2[1]); // write child -> parent
            
            // write a message for the child through the parent -> child pipe
            data_processed = write(file_pipes[1], buffer, strlen(buffer));
            printf("%d - wrote %d bytes\n", getpid(), data_processed);            
            close(file_pipes[1]); // write parent -> child
           
            int status;
            waitpid(fork_result, &status, 0);
            
            // read a message from the child through the child -> parent pipe
            data_processed = read(file_pipes2[0], buffer2, strlen(buffer));
            printf("%d - read %d bytes: %s\n", getpid(), data_processed, buffer2);
            close(file_pipes2[0]); // read child -> parent
        }
    }

    free(buffer);
    free(buffer2);

    exit(EXIT_SUCCESS);
}
