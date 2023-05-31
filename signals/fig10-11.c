#include <apue.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

static void sig_alarm_handler(int);

static jmp_buf env_jmp;

int main(void) {
	if (signal(SIGALRM, sig_alarm_handler) == SIG_ERR) {
		err_sys("signal handler register error");
	}
	alarm(10);

	char buf[MAXLINE];
	unsigned int sz = 0;

	if (setjmp(env_jmp) != 0) {
		// call came from sig_alarm_handler, thus exit
		err_sys("read timeout");
	}

	errno = 0;
	if ((sz = read(STDIN_FILENO, buf, MAXLINE)) == -1) {
		if (errno == EINTR) {
			err_sys("read timeout");
		}
		err_sys("read() error");
	}

	if (write(STDOUT_FILENO, buf, sz) == -1) {
		err_sys("write() error");
	}
	alarm(0);

	// will work, but is less flexible
	/* if (setjmp(env_jmp) == 0) {  // first time
		errno = 0;
		if ((sz = read(STDIN_FILENO, buf, MAXLINE)) == -1) {
			if (errno == EINTR) {
				err_sys("read timeout");
			}
			err_sys("read() error");
		}

		if (write(STDOUT_FILENO, buf, sz) == -1) {
			err_sys("write() error");
		}
		alarm(0);
	} */

	exit(0);
}

static void sig_alarm_handler(int signo) {
	// just pretend to do something, and exit the function
}


/** tries to solve the problem mentiond in fig10-10.c */

/** Problem:
 * still have problem with interaction with other signal handlers
 */
