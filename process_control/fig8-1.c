#include <apue.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int globvar = 6;
char buf[] = "writing something to stdout";

int main(void) {
	int val = 88;
	pid_t pid;

	if (write(STDIN_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1) {
		err_sys("error writing to stdout");
	}
	putc('\n', stdout);
	printf("before fork\n");

	if ((pid = fork()) < 0) {
		// error
		err_sys("fork error");
	} else if (pid == 0) {  // child process
		printf("from child: \n");
		val++;
		globvar++;
	} else {
		printf("from parent: \n");
		sleep(2);
	}

	printf("after fork: \n");
	printf("pid = %d, ppid = %d, glob = %d, val = %d\n", getpid(), getppid(), globvar, val);

	exit(0);
}
