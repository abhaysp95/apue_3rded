#include <apue.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
	pid_t pid;

	if ((pid = fork()) < 0) {
		err_sys("fork() error[1]");
	} else if (pid == 0) {  // first child
		if ((pid = fork()) < 0) {
			err_sys("fork() error[2]");
		} else if (pid == 0) {  // second child
			if ((pid = fork()) < 0) {
				err_sys("fork() error[3]");
			} else if (pid == 0) {  // third child
				if ((pid = fork()) < 0) {
					err_sys("fork() error[4]");
				} else if (pid == 0) {  // fourth child
					sleep(6);
					kill(getpid(), SIGKILL);
					_exit(6);
				} else {
					sleep(8);
					_exit(0);
				}
			} else {
				if (execl("/bin/dd", "dd", "if=/etc/hosts", "of=/dev/null", (char*)0) < 0) {
					err_sys("execl() error");
				}
				exit(7);
			}
		} else {
			sleep(4);
			abort();
		}
	} else {
		sleep(2);
		exit(2);
	}

	return 0;
}
