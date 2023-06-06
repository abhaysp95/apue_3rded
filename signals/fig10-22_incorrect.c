#include <apue.h>
#include <bits/types/sigset_t.h>
#include <signal.h>

int main(void) {
	sigset_t newmask, oldmask;
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);

	// block SIGINT and save current signal mask
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) == -1) {
		err_sys("sigprocmask() SIG_BLOCK error");
	}

	// critical region

	// restore signal mask (which unblocks SIGINT)
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) == -1) {
		err_sys("sigprocmask() SIG_SETMASK error");
	}

	// pause now
	pause();
}

/** problem: unblocking and sleep (pause) is not atomic for signal happening
 * between unblocking and pause, signals can be lost in this window and later
 * pause() can pause indefinitely */
