#include <apue.h>
#include <bits/types/sigset_t.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

/** program showing how to handler SIGTSTP (interactive stop), one of the job control signals */

static void sig_tstp_handler(int signo);
static void (*set_handler(int, void(*)(int)))(int);

int main(void) {
	// only job-control supported shell will have signal desposition of SIGTSTP
	// set to SIG_DFL
	void (*prev_desp)(int);  // simple function pointer variable
	if ((prev_desp = set_handler(SIGTSTP, SIG_IGN)) == SIG_DFL) {
		set_handler(SIGTSTP, sig_tstp_handler);
	} else if (prev_desp == SIG_ERR) {
		err_sys("set_handler() error checking SIGTSTP desposition");
	}

	// a simple interactive application
	int n;
	char buf[BUFSIZ];
	while ((n = read(STDIN_FILENO, buf, BUFSIZ)) > 0) {
		if (write(STDOUT_FILENO, buf, n) != n) {
			err_sys("write error");
		}
	}

	if (n < 0) {
		// check errno for more details
		err_sys("read error");
	}

	exit(0);
}

static void sig_tstp_handler(int signo) {
	/** move cursor to lower left corner, reset tty mode ...
	 * basically get the terminal back to previous state as it was before
	 * this (supposedly fullscreen) application
	 *
	 * unblock SIGTSTP, since signal is blocked because we're handling it rn
	 */
	sigset_t mask;
	sigemptyset(&mask);
	sigaddset(&mask, SIGTSTP);
	// can use SIG_UNBLOCK here (instead of generally recommended SIG_SETMASK, see sec-10.13)
	if (sigprocmask(SIG_UNBLOCK, &mask, NULL) == -1) {
		err_sys("sigprocmask() sigset_t unblocking error");
	}

	// reset SIGTSTP desposition to default
	if (set_handler(SIGTSTP, SIG_DFL) == SIG_ERR) {
		err_sys("set_handler() error setting SIGTSTP despotion to SIG_DFL");
	}
	// send (interactive) stop to ourself again
	kill(getpid(), SIGTSTP);  // this time, process will be stopped and won't return, until we recieve (like) SIGCONT

	// don't need to reset mask, cause if SIGTSTP was blocked by caller
	// before, any number of SIGTSTP is overridden by one SIGCONT and
	// vice-versa
	// reset handler reestablish signal handler
	if (set_handler(SIGTSTP, sig_tstp_handler) == SIG_ERR) {
		err_sys("set_handler() error reestablishing signal handler SIGTSTP");
	}

	// reset tty mode redraw your (fullscreen) application/screen ...
}

static void (*set_handler(int signo, void(*handler)(int)))(int) {
	struct sigaction act, oact;
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);  // if need to do any blocking, do here in the mask
	act.sa_flags = 0;

	if (signo == SIGALRM) {
#if defined SA_INTERRUPTED
		act.sa_flags |= SA_INTERRUPTED;
#endif
	} else {
		act.sa_flags |= SA_RESTART;
	}

	if (sigaction(signo, &act, &oact) == -1) {
		return SIG_ERR;
	}

	return oact.sa_handler;
}
