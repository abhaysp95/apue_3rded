#include <apue.h>
#include <pthread.h>
#include <stdio.h>

void cleanup(void *arg) {
	printf("cleanup: %s\n", (char*)arg);
}

void *thread_fn1(void *arg) {
	printf("thread1 start\n");
	pthread_cleanup_push(cleanup, "thread 1 handler 1");
	pthread_cleanup_push(cleanup, "thread 2 handler 2");
	if (arg) {
		return (void *)1; // generally not recommended to return in between of
						  // cleanup push & pop, because on some systems they
						  // maybe implemented as macro, as return doesn't
						  // invoke the cleanup handler. Only portable way to
						  // return between these 2 function is to use
						  // pthread_exit
	}
	pthread_cleanup_pop(0);  // don't execute the cleanup handler (arg == 0)
	pthread_cleanup_pop(0);
	return (void*)1;
}

void *thread_fn2(void *arg) {
	printf("thread2 start\n");
	pthread_cleanup_push(cleanup, "thread 2 handler 1");
	pthread_cleanup_push(cleanup, "thread 2 handler 2");
	if (arg) {
		pthread_exit((void*)2);
	}
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	return (void*)2;
}

int main(void) {
	pthread_t tid1, tid2;
	void *tret;
	int err;

	// try with arg == 0 too and see the cleanup behavior in both threads
	err = pthread_create(&tid1, NULL, thread_fn1, (void*)1);
	if (err != 0) {
		err_exit(err, "can't create thread1");
	}
	err = pthread_create(&tid2, NULL, thread_fn2, (void*)2);
	if (err != 0) {
		err_exit(err, "can't create thread2");
	}
	err = pthread_join(tid1, &tret);
	if (err != 0) {
		err_exit(err, "can't join thread 1");
	}
	printf("thread 1 exited with return value: %ld\n", (long)tret);
	err = pthread_join(tid2, &tret);
	if (err != 0) {
		err_exit(err, "can't join thread2");
	}
	printf("thread 2 exited with return value: %ld\n", (long)tret);
	exit(0);
}
