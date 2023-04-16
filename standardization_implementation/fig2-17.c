// determine the number of FDs

#include <apue.h>
#include <limits.h>
#include <errno.h>
#include <unistd.h>

#ifdef OPEN_MAX
static long openmax = OPEN_MAX;
#else
static long openmax = 0;
#endif

// if OPEN_MAX is indeterminate, this might be inadequate
#define OPEN_MAX_GUESS 256

long open_max() {
	if (0 == openmax) {
		errno = 0;
		if ((openmax = sysconf(_SC_OPEN_MAX)) < 0) {
			if (0 == errno) {
				openmax = OPEN_MAX_GUESS; // it's indeterminate
			} else {
				err_sys("sysconf error for _SC_OPEN_MAX");
			}
		}
	}

	return openmax;
}
