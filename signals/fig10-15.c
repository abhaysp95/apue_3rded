#include <apue.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static void sig_quit_handler(int);

int main(void) {
	sigset_t newmask, oldmask, pendmask;

	if (signal(SIGQUIT, sig_quit_handler) == SIG_ERR) {
		err_sys("can't catch SIGQUIT");
	}

	// block SIGQUIT and save current signal mask
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
		err_sys("SIG_BLOCK error");
	}

	sleep(5);  // SIGQUIT will remain pending here

	if (sigpending(&pendmask) < 0) {
		err_sys("sigpending error");
	}
	if (sigismember(&pendmask, SIGQUIT)) {
		printf("\nSIGQUIT pending\n");
	}

	// restore signal mask which unblocks SIGQUIT
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
		err_sys("SIG_SETMASK error");
	}
	printf("SIGQUIT unblocked\n");

	sleep(5);  // SIGQUIT here will terminate with core file

	exit(0);
}

static void sig_quit_handler(int signo) {
	printf("caught SIGQUIT\n");
	// need to register again the behavior on catching signal (unreliable signals)
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR) {
		err_sys("can't reset SIGQUIT");
	}
}

/**
 * NOTE: signals are queued in this system
 * ----------------------------------------
 *
 * From "man 7 signal"-:
 *
 * Standard  signals  do  not queue.  If multiple instances of a standard signal
 * are generated while that signal is blocked, then only one in‐ stance of the
 * signal is marked as pending (and the signal will be delivered just once when
 * it is unblocked).  In the case where a  standard signal  is  already pending,
 * the siginfo_t structure (see sigaction(2)) associated with that signal is not
 * overwritten on arrival of subse‐ quent instances of the same signal.  Thus,
 * the process will receive the information associated with the first instance
 * of the signal.
 *
 * Also: regarding blocked & pending signals
 * -----------------------------------------
 *
 * From "man 7 signal"-:
 *
 * A  signal may be blocked, which means that it will not be delivered until it
 * is later unblocked.  Between the time when it is generated and when it is
 * delivered a signal is said to be pending.
 * */
