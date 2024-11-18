#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static pthread_t getCurrentThreadID() {
    return pthread_self();
}

void *thrd_f1(void *);
void *thrd_f2(void *);
void err_sys(char *, int);
int sumUp(int n);
int factorial(int n);

int main() {
    pthread_t tid1, tid2;
    int rc;
    
    if ((rc = pthread_create(&tid1, NULL, thrd_f1, NULL)) != 0)
        err_sys("ERROR; return code from pthread_create() is: ", rc);
    
    if ((rc = pthread_create(&tid2, NULL, thrd_f2, NULL)) != 0)
        err_sys("ERROR; return code from prthread_create() is: ", rc);

    pthread_exit(NULL);
    return 0;
}

void *thrd_f1(void *arg) {
    int n;
    printf("Enter n value for sum up: ");
    scanf("%d", &n);

    printf("Sum is: %d\n", sumUp(n));
    pthread_exit(NULL);
}

void *thrd_f2(void *arg) {
    int n;
    printf("Enter n value for factorial: ");
    scanf("%d", &n);
    
    printf("Product is: %d\n", factorial(n));
    pthread_exit(NULL);
}

void err_sys(char* str, int code) {
    printf("%s%d\n", str, code);
    exit(1);
}

int sumUp(int n) {
    int sum = 0;

    for(int i = 1; i <= n; i++)
        sum = sum + i;

    return sum;
}

int factorial(int n) {
    int product = 1;

    if (n == 0) {
        return 1;
    }

    for (int i = 1; i <= n; i++)
        product = product * i;

    return product;
}

