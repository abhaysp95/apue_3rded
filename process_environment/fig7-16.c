#include <apue.h>
#include <stdio.h>
#include <sys/resource.h>

#define getlim(name) pr_limits(#name, name)

static void pr_limits(char *, int);

int main(void) {
#ifdef RLIMIT_AS
	getlim(RLIMIT_AS);
#endif

	getlim(RLIMIT_CORE);
	getlim(RLIMIT_CPU);
	getlim(RLIMIT_DATA);
	getlim(RLIMIT_FSIZE);

#ifdef RLIMIT_MEMLOCK
	getlim(RLIMIT_MEMLOCK);
#endif

#ifdef RLIMIT_MSGQUEUE
	getlim(RLIMIT_MSGQUEUE);
#endif

#ifdef RLIMIT_NICE
	getlim(RLIMIT_NICE);
#endif

	getlim(RLIMIT_NOFILE);

#ifdef RLIMIT_NPROC
	getlim(RLIMIT_NPROC);
#endif

#ifdef RLIMIT_NPTS
	getlim(RLIMIT_NPTS);
#endif

#ifdef RLIMIT_RSS
	getlim(RLIMIT_RSS);
#endif

#ifdef RLIMIT_SBSIZE
	getlim(RLIMIT_SBSIZE);
#endif

#ifdef RLIMIT_SIGPENDING
	getlim(RLIMIT_SIGPENDING);
#endif

	getlim(RLIMIT_STACK);

#ifdef RLIMIT_SWAP
	getlim(RLIMIT_SWAP);
#endif

#ifdef RLIMIT_VMEM
	getlim(RLIMIT_VMEM);
#endif

	exit(0);
}

static void pr_limits(char *name, int resource) {
	struct rlimit limit;
	unsigned long long lim;

	if (getrlimit(resource, &limit) < 0) {
		err_sys("getrlimit error fo %s", name);
	}

	printf("%-14s ", name);
	if (limit.rlim_cur == RLIM_INFINITY) {
		printf("(infinite) ");
	} else {
		lim = limit.rlim_cur;
		printf("%10lld ", lim);
	}

	if (limit.rlim_max == RLIM_INFINITY) {
		printf("(infinite)");
	} else {
		lim = limit.rlim_max;
		printf("%10lld", lim);
	}
	putchar((int)'\n');
}
