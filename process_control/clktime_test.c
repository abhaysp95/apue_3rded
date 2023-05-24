#include <apue.h>
#include <unistd.h>

int main(void) {
	static long clktime = 0;

#if defined(_SC_CLK_TCK)
	clktime = sysconf(_SC_CLK_TCK);
#else
#error _SC_CLK_TCK not found
#endif

	printf("clock ticks per second: %ld\n", clktime);

	exit(0);
}
