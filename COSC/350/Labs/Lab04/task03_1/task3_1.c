/*
 * Thomas Pearson
 * Lab04
 * task3_1.c
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

int main()
{
    const char* Dir1 = "/home/tpearson3/Dir1";
    const char* Dir2 = "/home/tpearson3/Dir2";
    const char* Dir21 = "/home/tpearson3/Dir2/Dir21";
    struct stat st;

    // check if dir1 exists
    if (stat(Dir1, &st) == -1) {
        // if dir1 doesn't exist make directory
        if (mkdir(Dir1, 0755) == 0)
            printf("Directory '%s' created successfully\n", Dir1);

    } else // directory dir1 already exists
        printf("Directory '%s' already exists\n", Dir1);

    // check if dir2 exists
    if (stat(Dir2, &st) == -1) {
        // if dir2 doesn't exist make directory
        if (mkdir(Dir2, 0755) == 0)
            printf("Directory '%s' created successfully\n", Dir2);

    } else // dir2 already exists
        printf("Directory '%s' already exists\n", Dir2);

    // check if directory 21 exists
    if (stat(Dir21, &st) == -1) {
        // if dir21 doesn't exist make directory
        if (mkdir(Dir21, 0755) == 0)
            printf("Directory '%s' created successfully\n", Dir21);

    } else // dir21 already exists
        printf("Directory '%s' already exists\n", Dir21);

    // copy hello file under ~/Dir2/Dir21
    int sourceFD, destFD, nbyte;
    int buffer_size = 1;
    char buffer[buffer_size];

    sourceFD = open("hello", O_RDONLY);
    destFD = open("/home/tpearson3/Dir2/Dir21/hello", O_WRONLY | O_CREAT | O_TRUNC, 0111);

    while((nbyte = read(sourceFD, buffer, buffer_size)) > 0)
        if (write(destFD, buffer, nbyte) != nbyte) {
            close(sourceFD);
            close(destFD);
            err_sys("Write Error!");
        }
    
    close(sourceFD);
    close(destFD);

    // make the symbolic link to Dir21
    char* target = "/home/tpearson3/Dir2/Dir21"; // directory to link
    char* linkpath = "/home/tpearson3/Dir1/toDir21"; // name for symlink (/home/tpearson3/Dir2/toDir21)

    // make the link
    if (symlink(target, linkpath) == -1 && !target)
        err_sys("error creating symbolic link");

    printf("Symbolic link '%s' created pointing to '%s'.\n", linkpath, target);

    // make the symbolic link to exe file helloe
    target = "/home/tpearson3/Dir2/Dir21/hello";
    linkpath = "/home/tpearson3/Dir1/toHello";

    if(symlink(target, linkpath) == -1)
        err_sys("error creating symbolic link");

    printf("Symbolic link '%s' created point to '%s'.\n", linkpath, target);

    return 0;
}