// #define _GNU_SOURCE

#include <features.h>
#include <apue.h>
#include <signal.h>

// static void dummy_sigaction_func(int, siginfo_t*, void *);

Sigfunc* signal(int signo, Sigfunc* handler_func) {  // Sigfunc defined in apue.h (is just typedef)
	struct sigaction act, oact;
	act.sa_handler = handler_func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	if (signo == SIGALRM) {
#if defined SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;
#endif
	} else {
		act.sa_flags |= SA_RESTART;
	}

	if (sigaction(signo, &act, &oact) < 0) {
		return SIG_ERR;
	}

	return oact.sa_handler;
}
