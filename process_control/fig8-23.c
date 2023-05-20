#include <apue.h>
#include <stdlib.h>
#include "./fig8-22.c"

int main(void) {
	int status;

	if ((status = my_system("date")) < 0) {
		err_sys("system() error");
	}
	pr_exit(status);

	if ((status = my_system("no_such_cmd")) < 0) {
		err_sys("system() error");
	}
	pr_exit(status);

	if ((status = my_system("who; exit 44")) < 0) {
		err_sys("system() error");
	}
	pr_exit(status);

	exit(0);
}
