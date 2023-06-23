#include <apue.h>
#include <pthread.h>

struct foo {
	int a, b, c, d;
};

void printfoo(const char *s, const struct foo *fp) {
	printf("%s", s);
	printf(" structure at 0x%lx\n", (unsigned long)fp);
	printf(" foo.a = %d\n", fp->a);
	printf(" foo.b = %d\n", fp->b);
	printf(" foo.c = %d\n", fp->c);
	printf(" foo.d = %d\n", fp->d);
}

void *thread_fn1(void *arg) {
	// struct foo foo = {1, 2, 3, 4};
	struct foo* foo = (struct foo*)malloc(sizeof(struct foo));
	*foo = (struct foo){1, 2, 3, 4};
	printfoo("thread 1: \n", foo);
	pthread_exit((void *)foo);
}

void *thread_fn2(void *arg) {
	printf("thread 2: ID is %lu\n", (unsigned long)pthread_self());
	pthread_exit((void *)0);
}

int main(void) {
	pthread_t tid1, tid2;
	struct foo *fp;

	int err = pthread_create(&tid1, NULL, thread_fn1, NULL);
	if (err != 0) {
		err_exit(err, "can't create thread 1");
	}
	pthread_join(tid1, (void *)&fp);
	if (err != 0) {
		err_exit(err, "can't join with thread1");
	}

	// actually, if you create foo on stack (thread1), upon return from
	// function (and in this case, also thread exit, it's lost and thus
	// wrong value. Although, stack of a thread can be modified by another
	// thread under same process)
	sleep(1);
	err = pthread_create(&tid2, NULL, thread_fn2, NULL);
	if (err != 0) {
		err_exit(err, "can't create thread 2");
	}
	sleep(1);
	printfoo("parent: \n", fp);

	exit(0);
}
