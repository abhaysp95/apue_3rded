#include <apue.h>
#include <pthread.h>



void *thread_fn1(void *arg) {
	printf("thread1 returning\n");
	return (void*)1;
}

void *thread_fn2(void *arg) {
	printf("thread2 returning\n");
	pthread_exit((void *)2);
}

int main(void) {
	pthread_t tid1, tid2;
	void *tret;

	int err = pthread_create(&tid1, NULL, thread_fn1, NULL);
	if (err != 0) {
		err_exit(1, "can't create thread1\n");
	}
	err = pthread_create(&tid2, NULL, thread_fn2, NULL);
	if (err != 0) {
		err_exit(1, "can't create thread2\n");
	}
	err = pthread_join(tid1, &tret);
	if (err != 0) {
		err_exit(1, "can't join with thread1\n");
	}
	printf("thread1 return value: %ld\n", (long)tret);
	err = pthread_join(tid2, &tret);
	if (err != 0) {
		err_exit(1, "can't join with thread2\n");
	}
	printf("thread2 return value: %ld\n", (long)tret);
	exit(0);
}
