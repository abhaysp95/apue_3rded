#include <apue.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int my_system(const char* cmdstring) {
	pid_t pid;
	int status = 0;

	if (cmdstring == NULL) {
		return 1;
	}

	if ((pid = fork()) < 0) {
		status = -1;
	} else if (pid == 0) {  // child
		if(execl("/bin/sh", "sh", "-c", cmdstring, (char*)0) < 0) {
			_exit(127);  // execl error
		}
	} else {  // parent
		errno = 0;
		while (waitpid(pid, &status, 0) < 0) {
			if (errno != EINTR) {
				status = -1;
				break;
			}
		}
	}

	return status;
}
