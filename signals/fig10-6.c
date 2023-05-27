#include <apue.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

static void sig_cld_handler(int);

int main(void) {

	pid_t pid;

	// linux uses SIGCHLD in place of SIGCLD (hence, here SIGCLD will behave as SIGCHLD)
	if (signal(SIGCLD, sig_cld_handler) == SIG_ERR) {
		err_sys("signal error");
	}
	if ((pid = fork()) < 0) {
		perror("fork() error");
	} else if (pid == 0) {  // child
		sleep(2);
		_exit(0);
	}

	pause();  // parent
	exit(0);
}

static void sig_cld_handler(int signo) {
	pid_t pid;
	int status;

	// pid will store child pid
	if ((pid = wait(&status)) < 0) {  // fetch child status
		perror("wait() error");
	}

	// signal generated again only after an/other child termination status
	if (signal(SIGCLD, sig_cld_handler) == SIG_ERR) {
		perror("signal() error");
	}

	printf("pid (terminated child): %d\n", pid);
}
