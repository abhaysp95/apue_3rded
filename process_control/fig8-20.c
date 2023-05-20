#include <apue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
	pid_t pid;

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {  // child process
		char buf[256];
		sprintf(buf, "%s/.local/bin/.scripts/testinterp", getenv("HOME"));
		if (execlp(buf, "testinterp", "myarg1", "MYARG2", (char*)0) < 0) {
			err_sys("execlp error");
		}
	}

	if (waitpid(pid, NULL, 0) < 0)  {
		err_sys("waitpid error");
	}

	exit(0);
}


/** content of testinterp file
 *
 * #!/${HOME}/.local/bin/.scripts/echoall foo
 *
 * replace ${HOME} with your home directory name
 */
