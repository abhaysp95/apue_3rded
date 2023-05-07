#include <apue.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {

	pid_t pid;

	if ((pid = fork()) < 0)  {
		err_sys("fork error");
	} else if (pid == 0) {  // child

		// fork for the child's child
		if ((pid = fork()) < 0) {
			err_sys("fork error");
		} else if (pid > 0) {  // parent from second fork == first child
			exit(0);  // no std I/O operations or such above, so exit() is safe
		}

		// second child;
		// my parent becomes init as soon as my original parent calls
		// exit() above. Continuing executing from here, knowing that
		// when I'm done, init will take care of our status (termination
		// status)
		sleep(2); // so that, first gen child (ie., my parent) can
				  // terminate before calling this printf) so that it
				  // will print ppid 1 and not it's parent (maybe
				  // because this child executed before it's parent)
		printf("second gen child, pid = %d, parent pid: %d\n", getpid(), getppid());
		exit(0);  // exit from second gen child

	}

	// parent, original parent of first child (no need for else, because
	// it's child is already exited and so is it's child's child)
	printf("big parent\n");
		// sleep(5); // so that, you wait for second gen child to print the above printf statement
	if (waitpid(pid, NULL, 0) != pid) {  // look for it's (only) child
		err_sys("waitpid error");
	}

	// parent (original process); I can continue executing here knowing that
	// I'm not the parent of second gen child ie., I'm not my own child
	// (else I would need that else {} block)

	exit(0);
}
