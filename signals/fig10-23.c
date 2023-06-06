#include <apue.h>
#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

// another use of sigsuspend is to wait for a signal handler to set a global variable

static sig_atomic_t quit_flag = 0;
static sig_atomic_t int_flag = 0;

static void sig_int_handler(int);
static void (*set_handler(int, void(*)(int)))(int);

int main(void) {
	sigset_t zeromask, newmask, oldmask;

	if (set_handler(SIGINT, sig_int_handler) == SIG_ERR) {
		err_sys("set_handler() SIGINT error");
	}
	if (set_handler(SIGQUIT, sig_int_handler) == SIG_ERR) {
		err_sys("set_handler() SIGQUIT error");
	}

	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);

	// block SIGQUIT
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) == -1) {
		err_sys("sigprocmask SIG_BLOCK error");
	}

	while (quit_flag == 0) {
		if (int_flag != 0) {  // if the handler was called, but with SIGINT
			printf("interrupted\n");
			int_flag = 0;
		}
		errno = 0;
		sigsuspend(&zeromask);  // will unblock SIGQUIT and thus it'll be able to call it's registered handler
		if (errno == EFAULT) {
			err_sys("sigsuspend error");
		}
	}

	// SIGQUIT blocked again, but we can proceed further
	quit_flag = 0;  // some reason you can think for your work (but not necessary here)
	printf("SIGQUIT recieved, proceeding further\n");

	// restore old mask which will unblock SIGQUIT
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) == -1) {
		err_sys("sigprocmask SIG_SETMASK error");
	}

	return 0;
}

static void sig_int_handler(int signo) {
	if (signo == SIGINT) {
		// not safe to use printf, since it is non-reentrant function (section 10.6)
		int_flag = 1;
	} else if (signo == SIGQUIT) {
		quit_flag = 1;
	}
}

static void (*set_handler(int signo, void(*handler)(int)))(int) {
	struct sigaction oact, act;
	act.sa_handler = handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);

	if (signo == SIGALRM) {
#if defined SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;  // don't restart the syscalls interrupted by alarm signals
#endif
	} else {
		act.sa_flags |= SA_RESTART;  // restart all interrupted syscalls automatically
	}

	if (sigaction(signo, &act, &oact) == -1) {
		// err_sys("sigaction [%s] error", strsignal(signo));
		return SIG_ERR;
	}

	return oact.sa_handler;
}
