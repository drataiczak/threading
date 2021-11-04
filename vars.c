#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int global = 0;

void *doWork(void *args) {
	long tid = (long) args;
	static int sint = 0;

	sint++;
	global++;

	printf("[%ld] Static: %d, Global %d\n", tid, sint, global);
}

int main() {
	pthread_t tid;

	for(long i = 0; i < 3; i++) {
		pthread_create(&tid, NULL, doWork, (void *)i);
	}

	pthread_exit(NULL);

	return 0;
}
