#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 1

void err_sys(char* str)
{
    printf("%s", str);
    exit(1);
}

int main()
{
    int inFileDes, outFileDes, nbyte;
    char buffer[BUFFER_SIZE];

    umask(0);

    inFileDes = open("test", O_RDONLY);
    outFileDes = open("hello6", O_WRONLY | O_CREAT, 0760);

    off_t inSize = lseek(inFileDes, 0, SEEK_END);

    if (inSize < 0)
        err_sys("lseek error!");

    for (off_t offset = inSize - 1; offset >= 0; offset--) {

        if ((nbyte = pread(inFileDes, buffer, BUFFER_SIZE, offset))<0)
            err_sys("read error!");

        if (pwrite(outFileDes, buffer, BUFFER_SIZE, inSize - offset - 1) != nbyte)
            err_sys("read error!");
    }


    return 0;
}
