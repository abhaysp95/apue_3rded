#include <apue.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>

// basic routine functions to help parent child to synchronize

static sig_atomic_t sig_flag = 0;
static sigset_t zeromask, newmask, oldmask;

static void sig_handler(int);
static void (*set_handler(int, void(*)(int)))(int);

static void sig_handler(int signo) {
	sig_flag = 1;
}

void TELL_WAIT(void) {
	if (set_handler(SIGUSR1, sig_handler) == SIG_ERR) {
		err_sys("set_handler(SIGUSR1) error");
	}
	if (set_handler(SIGUSR2, sig_handler) == SIG_ERR) {
		err_sys("set_handler(SIGUSR2) error");
	}

	sigfillset(&zeromask);
	sigdelset(&zeromask, SIGUSR1);
	sigdelset(&zeromask, SIGUSR2);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGUSR1);  // parent
	sigaddset(&newmask, SIGUSR2);  // child

	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) == -1) {
		err_sys("sigprocmask() SIG_BLOCK error");
	}
}

void TELL_PARENT(pid_t pid) {
	kill(pid, SIGUSR1);  // send signal to parent
}

void TELL_CHILD(pid_t pid) {
	kill(pid, SIGUSR2);  // send signal to child
}

/** well, WAIT_PARENT & WAIT_CHILD, are just like TELL_PARENT & TELL_CHILD. What
 * it means, is that a parent can invoke TELL_PARENT() (it should be
 * TELL_CHILD(), but that's the point) and child having WAIT_CHILD() (should be
 * WAIT_PARENT(), but anyways) will be cancelled, cause signal handler isn't
 * making any difference between signal sent for parent and signal sent for
 * child (which is not needed anyways, right now) */

void WAIT_PARENT() {
	while (sig_flag == 0) {
		errno = 0;
		sigsuspend(&zeromask);  // broke silence only when recieving
		if (errno == EFAULT) {
			err_sys("sigsuspend() error");
		}
	}
	// recieved signal
	sig_flag = 0;

	// reset the old mask
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) == -1) {
		err_sys("sigprocmask() SIG_SETMASK error");
	}
}

void WAIT_CHILD() {
	while (sig_flag == 0) {
		errno = 0;
		sigsuspend(&zeromask);
		if (errno == EFAULT) {
			err_sys("sigsuspend() error");
		}
	}
	// recieved signal
	sig_flag = 0;

	// reset to old mask
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) == -1) {
		err_sys("sigprocmask() SIG_SETMASK error");
	}
}

static void (*set_handler(int signo, void(*handler)(int)))(int) {
	struct sigaction act, oact;
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	if (signo == SIGALRM) {
#if defined SA_INTERRUPT
		// don't go restarting syscalls automatically if signal recieved is SIGALRM
		act.sa_flags |= SA_INTERRUPT;
#endif
	} else {
		act.sa_flags |= SA_RESTART;
	}

	if (sigaction(signo, &act, &oact) == -1) {
		return SIG_ERR;
	}

	return oact.sa_handler;  // return previous handler
}
