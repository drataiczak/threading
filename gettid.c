#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <threads.h>

void *doWork(void *args) {
    long tid = (long) args;

    printf("Thread %ld with ktid %d\n", tid, gettid());
    printf("Thread %ld with ktid %lu\n", tid, thrd_current());

    pthread_exit(NULL);
}

int main() {
    pthread_t tid;

    for(long i = 0; i < 10; i++) {
        pthread_create(&tid, NULL, doWork, (void *)i);
    }

    pthread_exit(NULL);

    return 0;
}