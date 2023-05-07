#include <apue.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "fig8-5.c"

/* int main(void) {
	pid_t pid;
	int status;

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {  // child
		exit(7);
	}

	if (wait(&status) != pid) {
		err_sys("wait error");
	}
	pr_exit(status);  // and print its status

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {
		abort();  // generates SIGABRT
	}

	if (wait(&status) != pid) {
		err_sys("wait error");
	}
	pr_exit(status);

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {
		status /= 0;  // generate SIGFPE
	}

	if (wait(&status) != pid) {
		err_sys("wait error");
	}
	pr_exit(status);

	exit(0);
} */

// equivalent to above program, but with waitpid(). Although, waitpid() is set
// to be non-blocking

int main(void) {
	pid_t pid;
	int status;

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {  // child
		exit(7);
	}

	if (waitpid(-1, &status, 0) != pid) {  // similar to wait()
		err_sys("wait error");
	}
	pr_exit(status);  // and print its status

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {
		abort();  // generates SIGABRT
	}

	if (waitpid(pid, &status, 0) != pid) {  // again, similar to wait()
		err_sys("wait error");
	}
	pr_exit(status);

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {
		status /= 0;  // generate SIGFPE
	}

	if (waitpid(-1, &status, 0) != pid) {
		err_sys("wait error");
	}
	pr_exit(status);

	exit(0);
}
