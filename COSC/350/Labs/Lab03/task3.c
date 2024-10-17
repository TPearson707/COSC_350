/*
 * Write a C program that
 * Copies the contents of a source file to a destination file
 * using a buffer of 32 bytes
 * output file must be created with specific permissions (rwx-rwx---, or 0770).
 * the program should demonstrate your knowledge of file I/O using system calls, buffer management, and file perms in C
 */

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 32

void err_sys(char* str)
{
    printf("%s", str);
    exit(1);
}

int main()
{
    int inFileDes, outFileDes, nbyte;
    char buffer[BUFFER_SIZE];

    // clear the mask to be able ot create a file with a mode
    umask(0);

    // open files for read only
    inFileDes = open("test", O_RDONLY);
    // open file for write only with permissions rwx-rwx---
    outFileDes = open("hello3", O_WRONLY | O_CREAT | O_TRUNC, 0770);

    while ((nbyte = read(inFileDes, buffer, BUFFER_SIZE)) > 0)
        if (write (outFileDes, buffer, nbyte) != nbyte)
            err_sys("Write Error!");

    close (inFileDes);
    close (outFileDes);

    return 0;
}
