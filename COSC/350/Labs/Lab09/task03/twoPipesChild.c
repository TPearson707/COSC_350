/* twoPipesChild.c */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int data_processed;
    char buffer[BUFSIZ + 1];
    char *buffer2 = "Hi, Mom!";
    int file_descriptor;
    int file_descriptor2;

    memset(buffer, '\0', sizeof(buffer));
    sscanf(argv[1], "%d", &file_descriptor);
    sscanf(argv[2], "%d", &file_descriptor2);

    // read from parent
    data_processed = read(file_descriptor, buffer, BUFSIZ);
    printf("%d - read %d bytes: %s\n", getpid(), data_processed, buffer);
    
    // write response back to parent
    data_processed = write(file_descriptor2, buffer2, strlen(buffer2));
    printf("%d - read %d bytes\n", getpid(), data_processed);
    
    close(file_descriptor);
    close(file_descriptor2);

    exit(EXIT_SUCCESS);
}
