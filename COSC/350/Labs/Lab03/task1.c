#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// ./program < file2copy > copyOfFile

#define BUFFER_SIZE 2
void err_sys(char* str)
{
    printf ("%s", str);
    exit(1);
}

int main()
{
    int nbyte;
    char buffer[BUFFER_SIZE];

    // read the file to copy
    while ((nbyte = read(STDIN_FILENO, buffer, BUFFER_SIZE)) >0)
        if (write (STDOUT_FILENO, buffer, nbyte) != nbyte) // valid write contents of old file to new file (copy)
            err_sys("Write Error");

    if (nbyte < 0)
        err_sys("read Error");

    exit(0);

}
