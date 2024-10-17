#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#define BUFFER_SIZE 1

void err_sys(char* str)
{
    printf ("%s", str);
    exit(1);
}

int main()
{
    int inFileDes, outFileDes, nbyte;
    char buffer[BUFFER_SIZE];

    umask(0);

    // open file for read only
    inFileDes = open("test", O_RDONLY);
    // open file for write only with permission rw-rw-rw
    outFileDes = open("hello2", O_WRONLY | O_CREAT | O_TRUNC, 0666);

    while ((nbyte = read(inFileDes, buffer, nbyte))> 0)
        if (write (outFileDes, buffer, nbyte) != nbyte)
            err_sys("Write Error!");

    close (inFileDes);
    close (outFileDes);
    exit(0);

}
