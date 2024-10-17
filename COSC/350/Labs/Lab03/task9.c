#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

void err_sys(const char* str) {
    write(2, str, strlen(str));
    exit(1);
}

int myatoi(char *str) {
    int num = 0;
    int index = 0;

    while (str[index] != '\0') {
        // Break if we hit a non-digit character
        if (str[index] < '0' || str[index] > '9') {
            break;
        }
        num = (num * 10) + (str[index] - '0');
        index++;
    }
    return num;
}

int main(int argc, char* argv[]) {

    int inFileDes, outFileDes;
    char buffer[BUFFER_SIZE];

    inFileDes = open(argv[1], O_RDONLY);
    outFileDes = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);

    while (read(inFileDes, buffer, sizeof(buffer) - 1) > 0) {
        buffer[BUFFER_SIZE - 1] = '\0';

        char *ptr = buffer;
        while (*ptr != '\0') {
            while (*ptr == ' ' || *ptr == '\n' || *ptr == '\r') {
                ptr++;
            }

            // Check if we're at the end of the buffer
            if (*ptr == '\0') break;

            // Find the end of the number
            char *end = ptr;
            while (*end >= '0' && *end <= '9') {
                end++;
            }
            *end = '\0';

            int num = myatoi(ptr);

            char ch = (char)num;
            if (write(outFileDes, &ch, 1) != 1) {
                err_sys("WRITE ERROR!\n");
            }

            ptr = end + 1;
        }
    }

    close(inFileDes);
    close(outFileDes);

    return 0;
}
