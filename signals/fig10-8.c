#include <apue.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>

static jmp_buf env_alarm;
// static int handler_counter = 0;

static void sig_alarm_handler(int signo) {
	// handler_counter++;
	longjmp(env_alarm, 1);
}

/** not complete implemention of sleep() */
unsigned int sleep2(unsigned int seconds) {
	if (signal(SIGALRM, sig_alarm_handler) == SIG_ERR) {
		return seconds;
	}
	if (setjmp(env_alarm) == 0) {  // first time calling (not when coming from longjmp)
		alarm(seconds);
		pause();
	}

	// testing something
	/* printf("handler counter: %d\n", handler_counter);
	printf("sleep again for 3 seconds\n");
	alarm(3);  // this will not go to handler (thus terminate)
	pause();
	printf("handler counter: %d\n", handler_counter); */

	return alarm(0);
}

/* int main(void) {
	printf("slept for 5 seconds\n");
	sleep2(5);
	// sleep2(3);
	// printf("slept for 3 seconds\n");

	exit(0);
} */

// NOTE: the commented parts show how signal() is unreliable
