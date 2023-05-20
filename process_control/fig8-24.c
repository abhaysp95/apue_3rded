#include <apue.h>
#include "./fig8-22.c"

int main(int argc, char **argv) {
	if (argc < 2) {
		err_exit(1, "usage: ./a.out <cmd_name>");
	}

	int status = 0;
	if ((status = my_system(argv[1])) < 0) {
		err_sys("system() error");
	}
	pr_exit(status);

	exit(0);
}
