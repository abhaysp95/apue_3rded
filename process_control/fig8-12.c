#include <apue.h>
#include <stdio.h>

// program demonstrating race condition between parent and child

void charatatime(char *);

int main(void) {
	pid_t pid;

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {
		charatatime("output from child\n");
	} else {
		charatatime("output from parent\n");
	}

	exit(0);
}

// function written like this, to allow the kernel to switch between processes
// as often as possible
void charatatime(char *str) {
	char *ptr;
	int c;

	setbuf(stdout, NULL);
	for (ptr = str, c = *ptr; (c = *ptr++) != 0;) {
		putc(c, stdout);
	}
}
