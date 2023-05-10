#include <apue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

char *env_init[] = { "USER=unknown", "PATH=/tmp", NULL };

int main(void) {
	pid_t pid;

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {  // specify pathname, specifiy environment
		char buf[256];
		memset(buf, 0, sizeof(buf));
		sprintf(buf, "%s/.local/bin/.scripts/echoall", getenv("HOME"));
		// printf("new path: %s\n", buf);
		if (execle(buf, "echoall", "myarg1", "MY ARG2", (char *)0, env_init) < 0) {
			err_sys("execle error");
		}
	}

	if (waitpid(-1, NULL, 0) < 0) {
		err_sys("wait error");
	}

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {  // specify filename, inherit environment
		if (execlp("echoall", "echoall", "only 1 arg", (char *)0) < 0)
			err_sys("execlp error");
	}

	exit(0);
}
