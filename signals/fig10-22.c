#include <apue.h>
#include <signal.h>
#include <errno.h>

static void sig_int_handler(int);

static void (*set_handler(int, void(*)(int)))(int);

int main(void) {
	sigset_t newmask, waitmask, oldmask;

	pr_mask("program start: ");

	if (set_handler(SIGINT, sig_int_handler) == SIG_ERR) {
		err_sys("signal() error");
	}

	sigemptyset(&newmask);
	sigemptyset(&waitmask);
	sigaddset(&newmask, SIGINT);
	sigaddset(&waitmask, SIGUSR1);

	// block SIGINT
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) == -1) {
		err_sys("sigprocmask() SIG_BLOCK error");
	}

	// enter critical region
	pr_mask("enter critical reason: ");

	// pause,allowing all signals except SIGUSR1
	errno = 0;
	sigsuspend(&waitmask);  // always returns -1
	if (errno == EFAULT) {  // not check for EITNR, because that's what we are testing for
		err_sys("sigsuspend error");
	}

	/** NOTE: SIGINT is recieved because, sigsuspend changed mask from
	 * newmask to waitmask for this thread, and SIGINT is not blocked in
	 * waitmask */

	pr_mask("after return from sigsuspend: ");

	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) == -1) {
		err_sys("sigprocmask() SIG_SETMASK error");
	}
	// critical region probably ends here

	// continue with rest of the programs
	pr_mask("exiting program: ");

	exit(0);
}

static void sig_int_handler(int signo) {
	pr_mask("\nsig_int_handler: ");
}

// implementation is already done in fig10-18.c, but doing again and again, to remember the basics
static void (*set_handler(int signo, void(*handler)(int)))(int) {
	struct sigaction act, oact;
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	if (signo == SIGALRM) {
#if defined SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;
#endif
	} else {
		act.sa_flags |= SA_RESTART;
	}

	if (sigaction(signo, &act, &oact) == -1) {
		return SIG_ERR;
	}

	return oact.sa_handler;
}

/** NOTE:
 * sigsuspend(): replace thread's current signal mask (each thread has signal mask) with the set of signal mask (passed as arg) and then suspend the thread until delivery of a signal whose action is either to exectue a signal-catching function or to terminate the process.
 *
 * So, if you want wake only on INTR signal
 * sigfillset(&mask);  // each signal is prepared to be set for blocking
 * sigdelset(&mask, SIGINTR);  // remote interrupt signal (don't block it)
 * sigsuspend(&mask);  // block every signal in mask and since INTR is not blocked, it will either terminate or execture registered handler
 *
 * If you want to block INTR
 * sigemptyset(&mask);
 * sigaddset(&mask, SIGINTR);
 * sigsuspend(&mask);  // will do nothing on recieveing interrupt and remain blocked here
 */
