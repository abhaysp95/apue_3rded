#include <apue.h>
#include <errno.h>
#include <signal.h>
#include <string.h>

static void _pr_mask_updated(const char* str) {
	sigset_t sigset;
	int errno_back;

	errno_back = errno;
	if (sigprocmask(0, NULL, &sigset) == -1) {
		err_ret("sigprocmask() error");
	} else {
		printf("%s", str);
		for (unsigned int i = 1; i <= SIGRTMAX; i++) {
			if (sigismember(&sigset, i)) {
				// no need of strdup here, because this is just for printing one time (see fig10-2.c in this folder)
				printf(" %s", strsignal(i));
			}
		}
		printf("\n");
	}

	errno = errno_back;
}

/** what's the relation between signal and priority ? (see definition of
 * SIGRTMAX & SIGRTMIN in signal.h for more) */
