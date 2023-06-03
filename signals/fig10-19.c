#include <apue.h>

Sigfunc* signal_itnr(int signo, Sigfunc* handler_func) {
	struct sigaction act, oact;

	act.sa_handler = handler_func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

#if defined SA_INTERRUPT
	act.sa_flags |= SA_INTERRUPT;
#endif

	if (sigaction(signo, &act, &oact) < 0) {
		return SIG_ERR;
	}

	return oact.sa_handler;
}
