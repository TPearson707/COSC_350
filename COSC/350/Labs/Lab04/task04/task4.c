/*
 * Thomas Pearson
 * Lab04
 * task4.c
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>

void err_sys(char* str)
{
    write(2, str, strlen(str));
    exit(1);
}

void mymv(char* file, char* dest_dir)
{

    
    if (dest_dir[strlen(dest_dir) - 1] == '/') {
	strcat(dest_dir, file);
    }

    if (link(file, dest_dir) == 0) { // move to new location
        if (unlink(file) == 0) { // unlink from old location
            printf("File moved successfully");
        } else {
            err_sys("error unlinking from source");
        }
    } else {
        err_sys("error linking to destination");
    }

    return;
}

int main(int argc, char* argv[])
{   

    if (argc < 1 || argc > 3)
        err_sys("Must enter arguments: filename, destination");

    char* file = argv[1];
    char* dest_dir = argv[2];

    mymv(file, dest_dir);

    return 0;
}
