#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *doWork(void *args) {
	sleep(5); // Just give it some time as if it was doing real work

	printf("[+] Inside of thread...\n");

	return NULL;
}

int main() {
	pthread_t tid;

	printf("[+] Before threads...\n");

	/* Creates thread and starts it
	 * Args:
	 * 	pthread_t * - Thread
	 *	const pthread_attr_t - Creates a thread with specific attrs
	 * 	(void *) (*func)(void * args) - Function pointer for work
	 * 	void *args - Arguments passed to thread
	 *
	 */
	pthread_create(&tid, NULL, doWork, NULL);
	
	/* Wait for thread to return 
	 * Args:
	 * 	pthread_t - Thread to wait for
	 * 	void **retval - Return value from the thread supplied to pthread_exit by the thread
	 */
	pthread_join(tid, NULL);

	printf("[+] Returned from threads...\n");

	return 0;
}
