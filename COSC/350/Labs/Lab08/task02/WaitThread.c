/* WaitThread.c */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int scores[20];

void *thread_f1(void *);
void *thread_f2(void *);
void *thread_f3(void *);
void *thread_f4(void *);
void err_sys(char *, int);

void swap(int* , int, int);
void bubbleSort(int*, int);

int main() {
    int rc;
    pthread_t tid1, tid2, tid3, tid4;
    void *tret1, *tret2, *tret3, *tret4;
    
    // create pthread 1
    if ((rc = pthread_create(&tid1, NULL, thread_f1, NULL)) != 0)
        err_sys("Error; return code from pthread_create() is", rc);
    
    // wait for pthread 1 to finish
    if ((rc = pthread_join(tid1, &tret1)) != 0)
        err_sys("Error; return code from pthread_join() is", rc);
    printf("Thread 1 exit code %d\n", (int)tret1);

    // create pthread 2
    if ((rc = pthread_create(&tid2, NULL, thread_f2, NULL)) != 0)
        err_sys("Error; return code from pthread_create() is", rc);

    // create pthread 3
    if ((rc = pthread_create(&tid3, NULL, thread_f3, NULL)) != 0)
        err_sys("Error; return code from pthread_create() is", rc);
    
    // wait for pthread 2 to finish
    if ((rc = pthread_join(tid2, &tret2)) != 0)
        err_sys("Error; return code from pthread_join() is", rc);
    printf("Thread 2 exit code %d\n", (int)tret2);

    // wait for pthread 3 to finish
    if ((rc = pthread_join(tid3, &tret3)) != 0)
        err_sys("Error; return code from pthread_join() is", rc);
    printf("Thread 3 exit code %d\n", (int)tret3);

    // create pthread 4
    if ((rc = pthread_create(&tid4, NULL, thread_f4, NULL)) != 0)
        err_sys("Error; return code from pthread_join() is", rc);
    
    // wait for pthread 4 to finish
    if ((rc = pthread_join(tid4, &tret4)) != 0)
        err_sys("Error; return code from pthread_join() is", rc);
    printf("Thread 4 exit code %d\n", (int)tret4);

    exit(0);
}

void *thread_f1(void *arg) {
    int n;
    int i = 0;
    while (1) {
        printf("Enter test score %d: ", i + 1);
        scanf("%d", &n);

        if (n == -1 || i == 19)
            break;

        scores[i] = n;
        i++;
    }
    
    printf("\n");

    sleep(1);
    printf("Thread 1 is about to finish\n");
    return ((void *) 1);

}

void *thread_f2(void *arg) {
    float average = 0;
    float medium = 0;
    int sum = 0;
    int n = sizeof(scores) / sizeof(scores[0]);
    int m = 0;
    
    // check if scores is null
    if (!scores) {
        printf("Error; scores is empty");
        sleep(1);
        printf("Thread 2 is about to finish\n");
        return ((void*) 2);
    }
    
    // find average
    for (int i = 0; i < n; i++) {
            if (scores[i] != 0) {
                sum += scores[i];
                m++;
            }
    }

    average = ((float)sum / (float)m);
    
    int temp[m];
    int counter = 0;

    // fill temp with valid scores
    for (int i = 0; i < n; i++) {
        if (scores[i] != 0) {
            temp[counter] = scores[i];
            counter++;
        }
    }
    
    // sort temp
    bubbleSort(temp, m);

    // get midpoint of scores
    int midpoint = (m - 1) / 2;
    
    // find medium value
    if (midpoint % 2 != 0)
        medium = (temp[midpoint] + temp[midpoint + 1]) / 2;
    else
        medium = temp[midpoint];

    printf("Average Score: %f\n", average);
    printf("Medium Value: %f\n", medium);
    
    sleep(1);
    printf("Thread 2 is about to finish\n");
    return ((void*) 2);
}


void *thread_f3(void *arg) {
    int min, max;
    int n = sizeof(scores) / sizeof(scores[0]);
    // check if scores is NULL
    if (!scores) {
        printf("Error; scores is empty");
        sleep(1);
        printf("Thread 3 is about to finish\n");
        return ((void*) 3);
    }
    
    min = scores[0];
    max = scores[0];

    // linear search of sorted array (check thread_f2) to find max and min
    for (int i = 0; i < n; i++) {
        if (min > scores[i] && scores[i] != 0)
            min = scores[i];
        if (max < scores[i])
            max = scores[i];
    }

    // print min and max
    printf("Minimum Score: %d\n", min);
    printf("Maximum Score: %d\n", max);

    sleep(1);
    printf("Thread 3 is about to finish\n");
    return ((void*) 3);
}

void *thread_f4(void *arg) {
    int n = sizeof(scores) / sizeof(scores[0]);
    
    for (int i = 0; i < n; i++) {
        scores[i] = 0;
    }
    
    for (int i = 0; i < n; i++)
        printf("%d ", scores[i]);
    printf("\n");

    sleep(1);
    printf("Thread 4 is about to finish\n");
    return ((void*) 4);
}

void err_sys(char *str, int code) {
    printf("%s %d\n", str, code);
    exit(1);
}

void swap(int *arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void bubbleSort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(arr, j, j + 1);
        }
    }
}
