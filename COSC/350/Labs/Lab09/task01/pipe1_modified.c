/* pipe1_modified.c */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int READ_END = 0;
int WRITE_END = 1;

int main() {
    int data_processed;
    int file_pipes[2];
    const char some_data[] = "123";
    int size = strlen(some_data);
    char *buffer = (char*) calloc(size, sizeof(char));
    
    if (!buffer) {
        printf("ERROR: Failed to allocate buffer\n");
        exit(1);
    }

    for (int i = 0; i < size + 1; i++) {
        buffer[i] = some_data[i];
    }

    if (pipe(file_pipes) == 0) {
        data_processed = write(file_pipes[1], some_data, strlen(some_data));
        printf("Wrote %d bytes\n", data_processed);
        data_processed = read(file_pipes[0], buffer, size);
        printf("Read %d bytes: %s\n", data_processed, buffer);

        free(buffer);

        exit(EXIT_SUCCESS);
    }

    free(buffer);
    exit(EXIT_FAILURE);
}
