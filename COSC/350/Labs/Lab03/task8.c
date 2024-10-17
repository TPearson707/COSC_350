#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BUFFER_SIZE 1
#define MAX_DIGITS 4

void err_sys(const char* message) {
    write(2, message, strlen(message));
    exit(1);
}

void write_ascii_value(int outFileDes, int ascii_value) {
    char ascii_str[MAX_DIGITS + 2];
    int len = snprintf(ascii_str, sizeof(ascii_str), "%d\n", ascii_value);

    if (write(outFileDes, ascii_str, len) != len) {
        err_sys("write error!");
    }
}

int main(int argc, char* argv[]) {

    int inFileDes = open(argv[1], O_RDONLY);
    int outFileDes = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);

    char buffer[BUFFER_SIZE];
    int bytesRead;

    while ((bytesRead = read(inFileDes, buffer, BUFFER_SIZE)) > 0) {
        int ascii_value = (unsigned char)buffer[0];
        write_ascii_value(outFileDes, ascii_value);
    }

    close(inFileDes);
    close(outFileDes);

    return 0;
}
