#include <apue.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int main(void) {
	struct timespec tout;
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	struct tm *tmp;
	char buf[64];

	pthread_mutex_lock(&mutex);
	printf("initial lock acquired\n");
	clock_gettime(CLOCK_REALTIME, &tout);
	tmp = localtime(&tout.tv_sec);
	strftime(buf, sizeof(buf), "%r", tmp);
	printf("current time is: %s\n", buf);
	tout.tv_sec += 10;
	// potential deadlock situtation here
	int err = pthread_mutex_timedlock(&mutex, &tout);
	clock_gettime(CLOCK_REALTIME, &tout);
	tmp = localtime(&tout.tv_sec);
	strftime(buf, sizeof(buf), "%r\n", tmp);
	printf("current time is: %s\n", buf);
	if (err == 0) {
		printf("mutex locked again\n");
	} else {
		printf("can't lock mutex again: %s\n", strerror(err));
	}
	exit(0);
}
