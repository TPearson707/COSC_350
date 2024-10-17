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
//     int inFileDes1, inFileDes2, outFileDes, nbyte;
//     char buffer[BUFFER_SIZE];
//
//     // umask to reset perms
//     umask(0);
//
//     inFileDes1 = open("test", O_RDONLY);
//
//     //outFileDes = open("hello4", O_WRONLY | O_CREAT, 0760);
//     outFileDes = open("hello4", O_WRONLY | O_CREAT | O_TRUNC, 0760);
//
//     // set place in outFile to append file2
//     if (lseek(outFileDes, 0, SEEK_END) < 0)
//         // if lseek returns < 0 (-1) we know we have an error
//         err_sys("lseek error");
//
//
//     while ((nbyte = read(inFileDes1, buffer, BUFFER_SIZE)) > 0)
//         if (write (outFileDes, buffer, nbyte) != nbyte)
//             err_sys("Write Error!");
//
//     close(inFileDes1);
//
//     inFileDes2 = open("test2", O_RDONLY);
//
//     // off_t lseek(int filedes, off_t offset, int whence);
//
//     // set place in outFile to append file2
//     if (lseek(outFileDes, 0, SEEK_END) < 0)
//         // if lseek returns < 0 (-1) we know we have an error
//         err_sys("lseek error");
//
//     while ((nbyte = read(inFileDes2, buffer, BUFFER_SIZE)) > 0)
//         if (write (outFileDes, buffer, nbyte) != nbyte)
//             err_sys("Write Error!");
//
//     close(inFileDes2);
//     close(outFileDes);
//
//     return 0;
// }

int main() {
    int inFileDes1, inFileDes2, outFileDes, nbyte;
    char buffer[BUFFER_SIZE];

    umask(0);

    inFileDes1 = open("test", O_RDONLY);
    inFileDes2 = open("test2", O_RDONLY);
    outFileDes = open("hello4", O_WRONLY | O_CREAT | O_TRUNC, 0666);

    while ((nbyte = read(inFileDes1, buffer, BUFFER_SIZE)) > 0)
        if (write(outFileDes, buffer, nbyte) != nbyte)
            err_sys("Write error");

    lseek(outFileDes, 0, SEEK_END);

    while ((nbyte = read(inFileDes2, buffer, BUFFER_SIZE)) > 0)
        if (write(outFileDes, buffer, nbyte) != nbyte)
            err_sys("Write error");

    close (inFileDes1);
    close (inFileDes2);
    close (outFileDes);

    return 0;
}




