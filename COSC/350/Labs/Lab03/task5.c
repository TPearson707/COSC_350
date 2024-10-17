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

// int main()
// {
//     int inFileDes, outFileDes, nbyte;
//     char buffer[BUFFER_SIZE];
//
//     umask(0);
//
//     inFileDes = open("test", O_RDONLY);
//     outFileDes = open("hello5", O_WRONLY | O_CREAT, 0760);
//
//     off_t inSize = lseek(inFileDes, 0, SEEK_END);
//
//     if (inSize < 0)
//         err_sys("lseek error");
//
//     for (off_t offset = inSize-1; offset >= 0; offset--) {
//
//         if (lseek(inFileDes, offset, SEEK_SET) < 0)
//             err_sys("lseek error");
//
//         if((nbyte = read(inFileDes, buffer, BUFFER_SIZE)) < 0)
//             err_sys("read error");
//
//         if (write (outFileDes, buffer, BUFFER_SIZE) != nbyte)
//             err_sys("write error");
//
//     }
//
//     close(inFileDes);
//     close(outFileDes);
//
//     return 0;
// }

int main()
{
    int inFileDes, outFileDes, nbyte;
    char buffer[BUFFER_SIZE];

    inFileDes = open("test", O_RDONLY);
    outFileDes = open ("hello5", O_WRONLY | O_CREAT | O_TRUNC, 0760);

    off_t inSize = lseek(inFileDes, 0, SEEK_END);

    for (off_t offset = inSize-1; offset >= 0; offset--) {
        lseek(inFileDes, offset, SEEK_SET);

        if((nbyte = read(inFileDes, buffer, BUFFER_SIZE)) < 0)
            err_sys("read error");

        if (write (outFileDes, buffer, nbyte) != nbyte)
            err_sys("write error");

    }

    close(inFileDes);
    close(outFileDes);

    return 0;
}
