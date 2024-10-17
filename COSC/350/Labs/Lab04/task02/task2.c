#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 1

void err_sys(char* str) {
    write(2, str, strlen(str));
    exit(1);
}

int myatoi(char* str) {

    int result;
    int sign = 1;

    if (*str == '-') { // check if there's negative numbers (in this case no)
        sign = -1;
        str++;
    }

    for (int i = 0; i < strlen(str); i++) {
        result = result * 10 + (str[i]-'0');
    }

    return sign * result;
}

void reverse(char str[], int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        end--;
        start++;
    }
}

char* myitoa(int num, char str[], int base) {
    int i = 0;
    int sign = 1;

    // handle 0
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    if (num < 0 && base == 10) {
        sign = -1;
        num = -num;
    }

    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    if (sign == -1)
        str[i++] = '-';

    str[i] = '\0';

    reverse(str, i);

    return str;
}

int main(int argc, char* argv[]) {
    if (argc > 2 || argc < 2)
        err_sys("Error: did not enter 1 file input");

    int inFileDes, nbyte;
    char buffer[BUFFER_SIZE];
    int num_buffer_size = 4;
    char num_buffer[num_buffer_size];

    inFileDes = open(argv[1], O_RDONLY); // open the inputted file

    int counter = 0;

    while ((nbyte = read(inFileDes, buffer, BUFFER_SIZE)) > 0) { // read file byte by byte
        if (isdigit(buffer[0])) { // if the character being read is an integer put in num_buffer
            num_buffer[counter] = buffer[0];
            counter++; // increment the iterator for num_buffer
        }
    }

    int result = myatoi(num_buffer); // run result through myatoi
    int sum = result + 10;

    char str[5];
    myitoa(sum, str, 10);

    if (write(1, str, 5) < 0)
        err_sys("Write Error!");



    return 0;
}
