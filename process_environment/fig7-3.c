#include <apue.h>
#include <stdio.h>
#include <stdlib.h>

static void exit_handler1();
static void exit_handler2();

int main(void) {
	if (atexit(exit_handler2) != 0) {
		err_sys("can't register exit_handler2");
	}
	if (atexit(exit_handler1) != 0) {
		err_sys("can't register exit_handler1");
	}
	if (atexit(exit_handler1) != 0) {
		err_sys("can't register exit_handler1");
	}

	printf("main out\n");
	exit(0);
}

static void exit_handler1() {
	printf("exit handler1\n");
}

static void exit_handler2() {
	printf("exit handler2\n");
}
