#include <apue.h>
#include <setjmp.h>
#include <signal.h>

static jmp_buf env_alarm;

static void sig_alarm_handler(int signo) {
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

	return alarm(0);
}
