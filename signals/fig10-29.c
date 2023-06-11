#include <apue.h>
#include <bits/types/sigset_t.h>
#include <signal.h>

static void sig_alarm_handler(int signo) {
	// nothing to do, just returning will waked sigsuspend
}

unsigned int sleep(unsigned int sec) {
	struct sigaction act, oact;
	act.sa_handler = sig_alarm_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	// set handler (and other settings for SIGALRM)
	if (sigaction(SIGALRM, &act, &oact) == -1) {
		err_sys("sigaction() SIGALRM error");
	}

	sigset_t newmask, oldmask, suspmask;
	sigemptyset(&newmask);
	// block SIGALRM
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) == -1) {
		err_sys("sigprocmask() SIG_BLOCK error");
	}

	alarm(sec);
	suspmask = oldmask;
	sigdelset(&suspmask, SIGALRM);  // confirm SIGALRM is not blocked anymore

	// wait for (unblocked) signal to be caught
	sigsuspend(&suspmask);  // check for any errors, like EFAULT if needed

	// some signal been caugh, SIGALRM is blocked again
	unsigned int ret = alarm(0);  // unslept time (if left) from previous alarm

	// set back previous action handler
	if (sigaction(SIGALRM, &oact, NULL) == -1) {
		err_sys("sigaction() SIGALRM error (unsetting)");
	}
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) == -1) {
		err_sys("sigprocmask() SIG_BLOCK error (old)");
	}

	return ret;
}
