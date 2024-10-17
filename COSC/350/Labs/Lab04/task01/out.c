#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1

// write an error to std_error and exit the program
void err_sys(char* str) {
    write(2, str, strlen(str));
    exit(1);
}

void write_to_file(int fileDes, char* buffer, int nbyte) {
    if (write(fileDes, buffer, nbyte) != nbyte)
        err_sys("Write Error!");
}

int main(int argc, char* argv[])
{
    int input, alpha, num, other, copy, nbyte;
    char buffer[BUFFER_SIZE];

    umask(0);

    input = open(argv[1], O_RDONLY);
    alpha = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0666);
    num = open(argv[3], O_RDWR | O_CREAT | O_TRUNC, 0666);
    other = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0666);
    copy = open(argv[5], O_RDWR | O_CREAT | O_TRUNC, 0666);

    while ((nbyte = read(input, buffer, BUFFER_SIZE))> 0) {

        // if newline, write it as is
        if (buffer[0] == '\n') {
            write_to_file(alpha, "\n", nbyte);
            write_to_file(num, "\n", nbyte);
            write_to_file(other, "\n", nbyte);
            continue;
        }

        // if alphabetic value, write to alpha
        if (isalpha(buffer[0])) {
            write_to_file(alpha, buffer, nbyte);
        } else {
            write_to_file(alpha, " ", nbyte); // write space if not alphabetic
        }

        // if digit, write to num
        if (isdigit(buffer[0])) {
            write_to_file(num, buffer, nbyte);
        } else {
            write_to_file(num, " ", nbyte); // write space if not digit
        }

        // if space or other character, write to other
        if (isspace(buffer[0])) {  // handle spaces correctly
            write_to_file(other, buffer, nbyte);  // write space as space
        } else if (!isdigit(buffer[0]) && !isalpha(buffer[0])) {
            write_to_file(other, buffer, nbyte);  // write other characters as is
        } else {
            write_to_file(other, " ", nbyte); // write space if alphabetic or digit
        }
    }

    int bSize = lseek(alpha, 0, SEEK_END);

    char a_buffer[bSize];
    char n_buffer[bSize];
    char o_buffer[bSize];



    if ((pread(alpha, a_buffer, bSize, 0)) < 0)
        err_sys("read error");

    if ((pread(num, n_buffer, bSize, 0)) < 0)
        err_sys("read error");

    if ((pread(other, o_buffer, bSize, 0)) < 0)
        err_sys("read error");

    // write the other characters to copy
    pwrite(copy, o_buffer, bSize, 0);

    // write the alphanumeric characters to copy
    for (int i = 0; i < bSize; i++) {
        if (isalpha(a_buffer[i])) {
            buffer[0] = a_buffer[i];
            pwrite(copy, buffer, 1, i);
        }
    }

    // write the numbers to copy
    for (int i = 0; i < bSize; i++) {
        if (isdigit(n_buffer[i])) {
            buffer[0] = n_buffer[i];
            pwrite(copy, buffer, 1, i);
        }
    }

    close(input);
    close(alpha);
    close(num);
    close(other);

    return 0;
}
