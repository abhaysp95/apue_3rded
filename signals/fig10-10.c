#include <apue.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

static void sig_alarm_handler(int);

int main(void) {
	if (signal(SIGALRM, sig_alarm_handler) == SIG_ERR)  {
		err_sys("signal() error");
	}
	alarm(10);
	char buf[MAXLINE];
	unsigned int sz = 0;
	errno = 0;
	if ((sz = read(STDIN_FILENO, buf, MAXLINE)) == -1) {
		if (errno == EINTR) {
			err_sys("read timeout");
		}
		err_sys("read() error");
	}
	alarm(0);  // read done, cancel the alarm

	if (write(STDOUT_FILENO, buf, sz) == -1) {
		err_sys("write() error");
	}

	exit(0);
}

static void sig_alarm_handler(int signo) {
	// ... just go back after interruption
}

/** Problem:
 * What if the process is blocked by kernel for more than 10 secs (because
 * alarm(10)) after raising alarm and then it comes to read ?
 * In this case, the read will blocked indefinitely
 * Mostly, to resolve this issue, alarm with long time arg is used
 *
 * If system call automatically restarts, read is not interrupted when SIGALRM
 * signal handler returns
 */
