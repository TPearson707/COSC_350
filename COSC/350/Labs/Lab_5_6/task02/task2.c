#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <utmp.h>

int openUtmpFile();
void err_sys(char *);

int main() {
    int fd, nbyte;
    
    fd = openUtmpFile();
    
    int numUsers = 0;
    struct utmp entry;
    
    while((nbyte = read(fd, &entry, sizeof(struct utmp))) > 0) {
        if (entry.ut_type == USER_PROCESS) {
            printf("%s\n", entry.ut_user);
            numUsers++;
        }
    }

    printf("The number of logged in users is %d\n", numUsers);


    close(fd);
    return 0;
}

int openUtmpFile() {
    int fd;
    
    fd = open("/var/run/utmp", O_RDONLY);

    if (fd  == -1) {
        err_sys("Error: could not open file exiting now");
    }  

    return fd;
}

void err_sys(char *str) {
    printf("%s", str);
    exit(1);
}
