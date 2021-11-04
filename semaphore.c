#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#define THREAD_COUNT 5

sem_t sem;

void *doWork(void *args) {
    long tid = (long) args;

    printf("[%ld] Waiting on semaphore\n", tid);
    sem_wait(&sem);
    printf("[%ld] In critical section\n", tid);
    sem_post(&sem);
    printf("[%ld] Semaphore released\n", tid);
}

int main() {
    pthread_t threadpool[THREAD_COUNT];

    if(0 != (sem_init(&sem, 0, 1))) {
        fprintf(stderr, "[!] Failed to create semaphore...\n");
        return -1;
    }

    for(long i = 0; i < THREAD_COUNT; i++) {
        if(0 != (pthread_create(&threadpool[i], NULL, doWork, (void *) i))) {
            fprintf(stderr, "[!] Unable to create thread\n");
            return -1;
        }
    }

    for(int j = 0; j < THREAD_COUNT; j++) {
        pthread_join(threadpool[j], NULL);
    }

    sem_destroy(&sem);

    return 0;
}