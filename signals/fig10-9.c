#include <apue.h>
#include <signal.h>
#include <stdio.h>

unsigned int sleep2(unsigned int);
static void sig_int_handler(int);

int main(void) {

	if ((signal(SIGINT, sig_int_handler)) == SIG_ERR) {
		err_sys("signal() error");
	}
	unsigned int unslept = sleep2(5);  // also try out behavior with sleep2(100) ie., let sigint handler complete full
	printf("sleep2 returned: %u\n", unslept);

	exit(0);
}

// trying to make this handler run atleast more than 5 secs (to showcase the problem of longjmp in sleep2)
static void sig_int_handler(int signo) {
	volatile long k = 0;  // prevent optimizing compiler from avoiding loop

	printf("sig int handler started\n");
	for (unsigned int i = 0; i < 1e5; i++) {
		for (unsigned int j = 0; j < 1e5; j++) {
			k += (i * j);
		}
		k %= (int)(1e9 + 7);
	}
	printf("sig int handler finished\n");
}
