#include <apue.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void charatatime(char *);

int main(void) {
	pid_t pid;

	TELL_WAIT();

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {
		// WAIT_PARENT();  // wait for parent (maybe to signal)
		charatatime("output from child");
		TELL_PARENT(getppid());  // tell parent once the work is done
	} else {
		WAIT_CHILD();  // wait for child's response before starting
		charatatime("output from parent");
		// TELL_CHILD(pid);  // tell child (maybe signal)
	}

	exit(0);
}

void charatatime(char *str) {
	int c = '\0';

	setbuf(stdout, NULL);
	for (c = *str; (c = *str++) != 0;) {
		putc(c, stdout);
	}

	// just testing out something
	/* c = **str;  // change parameter to **
	while (c != 0) {
		*str = (*str)++;
		c = **str;
	} */
}
