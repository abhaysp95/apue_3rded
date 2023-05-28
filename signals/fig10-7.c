#include <apue.h>
#include <signal.h>
#include <unistd.h>

static void sig_alarm_handler(int signo) {
	// .. do something to handle this signal
}

unsigned int sleep1(unsigned int seconds) {
	if (signal(SIGALRM, sig_alarm_handler) == SIG_ERR) {
		return seconds;
	}
	alarm(seconds);  // raise alarm after "seconds" seconds
	pause();  // wait until the signal occurs
	return (alarm(0));  // turn off the timer, and return the left time from prev. alarm (unslept time)
}
