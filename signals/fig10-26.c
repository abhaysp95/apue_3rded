#include <apue.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>

// why signal is needed for system()

// system() clone (same as fig8-13.c)
static int sysclone(const char *cmd);

static void sig_int_handler(int);
static void sig_chld_handler(int);

static void (*set_handler(int, void(*)(int)))(int);

int main(void) {
	if (set_handler(SIGINT, sig_int_handler) == SIG_ERR) {
		err_sys("set_handler SIGINT error");
	}
	if (set_handler(SIGCHLD, sig_chld_handler) == SIG_ERR) {
		err_sys("set_handler SIGCHLD error");
	}

	printf("[main] parent pid: %d\n", getpid());

	if (sysclone("ed") < 0) {
		err_sys("sysclone() error");
	}

	exit(0);
}

static void sig_int_handler(int signo) {
	// shouldn't use printf in signal handler (but this is for testing here)
	printf("caught SIGINT\n");
}

static void sig_chld_handler(int signo) {
	printf("caught SIGCHLD\n");
}

static int sysclone(const char *cmd) {
	if (cmd == NULL) {
		return 1;
	}

	int status = 0;
	pid_t pid;

	if ((pid = fork()) < 0) {
		return status;
	} else if (pid == 0) { // child
		if (execl("/bin/sh", "sh", "-c", cmd, (char*)NULL) == -1) {
			// check errno for more specific error (man 2 execve)
			_exit(127);
		}
	} else {  // parent
		printf("[system] parent pid: %d\n", getpid());
		errno = 0;
		while (waitpid(pid, &status, 0) == -1) {
			// here EINTR is generated when "WNOHANG  was  not  set
			// and an unblocked signal or a SIGCHLD was caught"
			if (errno != EINTR) {
				status = -1;
				break;
			}
		}
	}

	return status;
}

static void (*set_handler(int signo, void (*handler)(int)))(int) {
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
