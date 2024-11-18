/* mygetenv.c, my personal implementation of mygetenv.c */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern char **environ;

int mystrstr(const char *, const char *); /* checks to see where the first occurance of a string is */
char *mygetenv(const char *name); /* my own get env function */
size_t getsize(const char *); /* loops through a c-string to determie size n; returns size n */ 

int main()
{
    
    printf("HOME=%s\n", mygetenv("HOME"));
    printf("PATH=%s\n", mygetenv("PATH"));
    printf("ROOTPATH=%s\n", mygetenv("ROOTPATH"));
    printf("SHELL=%s\n", mygetenv("SHELL"));
    printf("USER=%s\n", mygetenv("USER"));
    printf("PWD=%s\n", mygetenv("PWD"));
    printf("LANG=%s\n", mygetenv("LANG"));
    printf("EDITOR=%s\n", mygetenv("EDITOR"));
	return 0;
}

int mystrstr(const char *haystack, const char *needle) {

    if (haystack == NULL || needle == NULL) {
        printf("Error: haystack or needle are NULL");
        exit(1);
    }

    size_t size = getsize(needle);

    

    for (int i = 0; i < size; i++)
        if (haystack[i] != needle[i])
            return -1;

    return 1;

}

char *mygetenv(const char *name) {
    if (name == NULL)
        return "name entered is null";

    size_t size = getsize(name);
    
    char **env = environ;

    while (*env) {
        if (mystrstr(*env, name) == 1) {
            char *ptr = *env + size + 1;
            return ptr;
        }
        *env++;
    }

    return "(null)";
}

size_t getsize(const char *str) {
    size_t n = 0;

    while(str[n] != '\0')
        n++;
    
    return n;
}

