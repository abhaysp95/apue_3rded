#include <apue.h>
#include <signal.h>
#include <stdio.h>

void abort(void) {
	sigset_t mask;
	struct sigaction action;

	// caller can't ignore SIGABRT, if so reset to default
	sigaction(SIGABRT, NULL, &action);
	if (action.sa_handler == SIG_IGN) {
		action.sa_handler = SIG_DFL;
		sigaction(SIGABRT, &action, NULL);
	}
	if (action.sa_handler == SIG_DFL) {
		fflush(NULL);  // flush all open stdio streams (not same as fclose)
	}

	// caller can't block SIGABRT; make sure it's unblocked
	/** NOTE: POSIX.1 specifies taht abort overrides the blocking or
	 * ignoring of the signal by the process */
	sigfillset(&mask);
	sigdelset(&mask, SIGABRT);
	sigprocmask(SIG_SETMASK, &mask, NULL);  // only turn on SIGABRT
	kill(getpid(), SIGABRT);  // send the signal

	/** NOTE: if kill() causes the signal to be generated for caller, and if
	 * the signal in unblocked, then signal (or some other pending,
	 * unblocked signals) are delivered to the process before kill returns.
	 *
	 * Blocking all the signals except SIGABRT (SIGTERM & SIGKILL are
	 * exception) tells that if the call to kill returns, the process caught
	 * the signal and the signal handler returned, unless we used exit,
	 * _exit, _Exit, longjmp or siglongjmp from the handler
	 *
	 * The first call of kill() also deals with custom handler and
	 * thus if we're here, process caught SIGABRT and returned (the below
	 * code shouldn't be exeucted unless the SIGABRT was registered to
	 * custom signal handler */

	fflush(NULL);  // flush all open stdio streams

	action.sa_handler = SIG_DFL;
	sigaction(SIGABRT, &action, NULL);  // reset handler action as default
	sigprocmask(SIG_SETMASK, &mask, NULL);
	kill(getpid(), SIGABRT);
	exit(1);  // this should never be executed (cause default action is terminate+core)
}
