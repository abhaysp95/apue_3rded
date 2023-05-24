#include <apue.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>

// with global vars, both parent and child will have copy of its own (which is
// not always the case with autoval, depending on optimization)
unsigned long long count = 0;
struct timeval end;

// uint8_t checktime(char *str, unsigned long long count, const struct timeval* end) {
uint8_t checktime(char *str) {
	struct timeval cur;

	gettimeofday(&cur, NULL);
	if (cur.tv_sec >= end.tv_sec && cur.tv_usec >= end.tv_usec) {
		printf("%s count = %llu	\n", str, count);
		return 1;
	}

	return 0;
}

int main(int argc, char **argv) {
	pid_t pid = 0;
	char *whoami = NULL;
	int nzero = 0;
	long adj = 0;

	if (argc > 2) {
		err_quit("usage: ./a.out [incr]");
	}
	if (argc == 2) {
		adj = strtol(argv[1], NULL, 10);  // check "man strtol" for knowing the mid arg.
	}

	setbuf(stdout, NULL);
#if defined(NZERO)
	nzero = NZERO;
#elif defined(_SC_NZERO)
	nzero = sysconf(_SC_NZERO);
#else
#error NZERO undefined
#endif
	gettimeofday(&end, NULL);
	end.tv_sec += 10;  // run for 10 seconds

	if ((pid = fork()) < 0) {
		err_sys("fork() error");
	} else if (pid == 0) {  // child
		whoami = "child";
		printf("nzero = %d, current nice value in child is: %d, adjusting it with %ld\n",
				nzero, nice(0) + nzero, adj);
		int ret = nice(adj);
		errno = 0;
		if (ret == -1 && errno != 0) {
			err_sys("child set scheduling priority");
		}
		printf("now child nice value is %d\n", nice(0) + nzero);
	} else {  // parent
		whoami = "parent";
		printf("nzero = %d, current nice value in parent is: %d\n", nzero, nice(0) + nzero);
	}

	while (1) {
		// what if unsigned data type crosses its threshold (we know if
		// unsigned get -ve value, it rounds off to it's greatest side,
		// but what if greatest is still less for some purpose)
		count++;
		if (checktime(whoami)) {
			exit(0);
		}
	}

	exit(0);
}

/**
 * NOTE: how can I measure cpu usage for these 2 process (parent & child)
 * seperately and same for process times for these two ?
 */
