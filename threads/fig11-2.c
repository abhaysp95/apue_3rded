#include <apue.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

pthread_t ntid;

void printids(const char* s) {
	pid_t pid;
	pthread_t tid;

	pid = getpid();
	tid = pthread_self();

	printf("%s pid %lu tid %lu (0x%lx)\n", s, (unsigned long)pid, (unsigned long)tid, (unsigned long)tid);
}

void *thread_fn(void *arg) {
	printids("new thread: ");
	return (void *)0;
}

int main(void) {
	int err;
	err = pthread_create(&ntid, NULL, thread_fn, NULL);

	/** ntid does have new thread id, but it's possible that new thread runs
	 * before main thread returns call from pthread_create and ntid is
	 * uninitialized (or possibly default/wrong) value */

	if (err != 0) {
		err_exit(err, "can't create new thread");
	}
	printids("main thread: ");
	sleep(1);  // join functionality not introduced yet
	exit(0);
}
