#include <apue.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv) {
	if (argc < 2) {
		err_exit(1, "usage: ./test <incr value>");
	}

	int nzero = 0;
	long adj = strtol(argv[1], NULL, 10);

#if defined (_SC_NZERO)
	nzero = sysconf(_SC_NZERO);  // default nice value of system
#else
#error "NZERO not defined"
#endif

	printf("nice value: %d\n", nice(0));
	printf("nice value + nzero: %d\n", nice(0) + nzero);
	errno = 0;
	int ret = nice(adj);
	if (ret == -1 && errno != 0) {
		err_sys("error with nice(adj)");
	}
	printf("nice updated, ret value: %d\n", ret);
	printf("nice updated, ret value: %d\n", ret + nzero);
	printf("nice value: %d\n", nice(0));
	printf("nice value + nzero: %d\n", nice(0) + nzero);

	exit(0);
}
