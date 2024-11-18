#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void Bye1(void *);
void Bye(void *);
void *Thread1 (void *);
void *Thread2 (void *);

int main () {
    pthread_t main_thread, first_thread, second_thread;
    int rc = 0;
    main_thread = pthread_self();

    pthread_cleanup_push(Bye1, NULL);

    rc = pthread_create(&second_thread, NULL, Thread1, (void *)main_thread);
    rc = pthread_create(&first_thread, NULL, Thread2, (void *)second_thread);

    while (1) {
        printf("In the original thread!\n");
        pthread_testcancel();
        sleep(1);
    }
    pthread_cleanup_pop(0);
    return 0;
}

void Bye1(void *arg) {
    printf("END OF PROGRAM");
}

void Bye(void *arg) {
    pthread_t tid = (pthread_t)arg;
    int rc;
    printf("The first thread job is done!\n");
    rc = pthread_cancel(tid);
}

void *Thread1(void *arg) {
    pthread_t main_thread = (pthread_t) arg;
    printf("Entered the first thread\n");
    pthread_cleanup_push(Bye, (void *)main_thread);
    while (1) {
        printf("In the first thread\n");
        pthread_testcancel();
        sleep(1);
    }
    pthread_cleanup_pop(0);
}

void *Thread2(void *arg) {
    int count, rc;
    pthread_t first_thread = (pthread_t)arg;
    printf("Entered the second thread\n");

    for (count = 1; count <= 10; count++) {    
        printf("In the second thread\n");
        sleep(1);
    }
    rc = pthread_cancel(first_thread);
    printf("The second thread job is done!\n");
}


