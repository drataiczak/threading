#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_COUNT 5

pthread_mutex_t lock;
int shared = 0;

void *doWork(void *args) {
    long tid = (long) args;


    printf("[%ld] Attempting to get mutex\n", tid);

    pthread_mutex_lock(&lock);

    shared = tid;
    printf("[%ld] Setting shared to %ld\n", tid, tid);

    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);
}

int main() {
    pthread_t tid[THREAD_COUNT];

    pthread_mutex_init(&lock, NULL);

    for(int i = 0; i < THREAD_COUNT; i++) {
        int ret = pthread_create(&tid[i], NULL, doWork, (void *)((long) i));
        if(ret != 0) {
            fprintf(stderr, "[!] Unable to create thread: %d\n", ret);
            return -1;
        }
    }

    for(int j = 0; j< THREAD_COUNT; j++) {
        pthread_join(tid[j], NULL);
    }

    return 0;
}