/*
 * argc (argument count)
 * argv (argument vector)
 */

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int str_to_int(char* str)
{
    int result = 0;
    int sign = 1;

    if (*str == '-') {
        sign = -1;
        str++;
    }

    while (*str) {
        result = result * 10 + (*str - '0');
        str++;
    }

    return sign * result;
}

int main(int argc, char* argv[])
{
    int sum = 0;

    for (int i = 1; i < argc; i++) {
        sum += str_to_int(argv[i]);
    }

    printf("The sum is: %d", sum);

    return 0;
}
