#include <apue.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int globvar = 20;  // global variable

int main(void) {
	int autovar = 10;  // automatic variable
	pid_t pid;

	printf("before fork\n");
	if ((pid = vfork()) < 0) {
		err_sys("error calling vfork");
	} else if (pid == 0) {  // child process
		globvar++;
		autovar++;
		_exit(0); // doesn't do any flushing (unlike exit()), maybe
				  // necessary for some std I/O lib function you're
				  // using, depending on implentation, it could result
				  // in indeterminate behaviour
	} else {
		// for parent, if you want anything here
	}

	// with vfork, it's garaunteed that child will execute first until it
	// calls exit() or exec(), upon which parent will execute. There can be
	// deadlock if child wants to depend on some action from parent before
	// calling any of these two functions

	// parent continues here (child will not reach, cause it exited)
	printf("pid = %d, ppid = %d, globvar = %d, autovar = %d\n", getpid(), getppid(), globvar, autovar);

	// the change is made in the parent space by child, because vfork() make
	// child run in the parent's address space (even if there's change to be
	// made on parent's address space), unlike some modern implentation of
	// fork which support COW (copy-on-write)

	exit(0);
}
