#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>

void err_sys(char* str)
{
    write(2, str, strlen(str));
    exit(1);
}

int main()
{
    int outFileDes, nbyte;

    if((outFileDes = open("hello", O_CREAT | O_TRUNC, 0111)) < 0)
        err_sys("Could not open file");
    
    close(outFileDes);

    return 0;
}