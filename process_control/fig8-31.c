#include <apue.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <time.h>
#include <unistd.h>

static void do_cmd(char *cmd);
static void pr_times(clock_t real, const struct tms* start, const struct tms* end);

int main(int argc, char **argv) {

	setbuf(stdout, NULL);  // write asap

	for (size_t i = 1; i < argc; i++) {
		do_cmd(argv[i]);
	}

	exit(0);
}

static void do_cmd(char *cmd) {
	struct tms tmsstart, tmsend;
	clock_t start, end;  // for elapsed wall clock time

	printf("ncommand: %s\n", cmd);

	if ((start = times(&tmsstart)) == -1) {
		err_sys("times error");
	}
	int status = 0;
	if ((status = system(cmd)) < 0) {
		err_sys("system() error");
	}
	if ((end = times(&tmsend)) == -1) {
		err_sys("times error");
	}

	pr_times(end - start, &tmsstart, &tmsend);
	pr_exit(status);
}

static void pr_times(clock_t real, const struct tms* start, const struct tms* end) {
	static long clktck = 0;

	if (0 == clktck) {
#if defined(_SC_CLK_TCK)
		if ((clktck = sysconf(_SC_CLK_TCK)) < 0) {
			err_sys("sysconf error");
		}
#else
#error _SC_CLK_TCK not defined
#endif
	}

	printf("\treal: %7.2f\n", real / (double) clktck);
	printf("\tuser: %7.2f\n", (end->tms_utime - start->tms_utime) / (double) clktck);
	printf("\tsystem: %7.2f\n", (end->tms_stime - start->tms_stime) / (double) clktck);
	printf("\tchild user: %7.2f\n", (end->tms_cutime - start->tms_cutime) / (double) clktck);
	printf("\tchild system: %7.2f\n", (end->tms_cstime - start->tms_cstime) / (double) clktck);
}
