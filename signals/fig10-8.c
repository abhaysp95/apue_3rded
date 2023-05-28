#include <apue.h>
#include <setjmp.h>
#include <signal.h>

static jmp_buf env_alarm;

static void sig_alarm_handler(int signo) {
	longjmp(env_alarm, 1);
}

unsigned int sleep2(unsigned int seconds) {
	if (signal(SIGALRM, sig_alarm_handler) == SIG_ERR) {
		return seconds;
	}
	if (setjmp(env_alarm) == 0) {  // first time calling (not when coming from longjmp)
		alarm(seconds); // if alarm() executes and signal handler is
						// called before pause(), then pause() will not be
						// executed because of this if block condition and
						// thus process will not wait indefinitely
		pause();
	}

	return alarm(0);
}
