#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 256

void err_sys(char* str)
{
    write(2, str, strlen(str));
    exit(1);
}


int palind(int fd1, int fd2)
{
    char buf1, buf2;
    int size = lseek(fd2, -2, SEEK_END);
    int curr;
    // Compares the back of the file to the front of the file
    for(curr = 0; curr < size; curr++)
    {
        lseek(fd1, curr, SEEK_SET);
        read(fd1, &buf1, 1);
        lseek(fd2, -2 - curr, SEEK_END);
        read(fd2, &buf2, 1);

        //printf("%c = %c \n", buf1, buf2);
        if(buf1 != buf2)
            return 0;
    }
    return 1;
}


int main(int argc, char* argv[])
{
    int fd1, fd2;
    char* input = argv[1];

    fd1 = open(input, O_RDONLY);

    if (fd1 < 0)
        err_sys("Could not open file to fd1");

    fd2 = dup(fd1);

    if (fd2 < 0)
        err_sys("Could not open file to fd2");

    int is_palindrome = palind(fd1, fd2);

    char* p_str_1 = "The contents of the file are a palindrome";
    char* p_str_2 = "The contents of the file are not a palindrome";

    if (is_palindrome) {
        write(1, p_str_1, strlen(p_str_1));
    } else{
        write(1, p_str_2, strlen(p_str_2));
    }

    close(fd1);
    close(fd2);

    return 0;
}
