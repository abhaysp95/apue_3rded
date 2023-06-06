#include <apue.h>
#include <errno.h>
#include <signal.h>

void pr_mask(const char* str) {
	sigset_t sigset;
	int errno_back;

	errno_back = errno;
	if (sigprocmask(0, NULL, &sigset) < 0) {
		err_ret("sigprocmask() error");
	} else {
		printf("%s", str);
		if (sigismember(&sigset, SIGINT)) {  // 1 if set, 0 if not
			printf(" SIGINT");
		}
		if (sigismember(&sigset, SIGQUIT)) {  // 1 if set, 0 if not
			printf(" SIGQUIT");
		}
		if (sigismember(&sigset, SIGUSR1)) {  // 1 if set, 0 if not
			printf(" SIGUSR1");
		}
		if (sigismember(&sigset, SIGUSR2)) {  // 1 if set, 0 if not
			printf(" SIGUSR2");
		}
		if (sigismember(&sigset, SIGALRM)) {  // 1 if set, 0 if not
			printf(" SIGALRM");
		}

		// ... and so on for the rest of the signals
		printf("\n");
	}

	errno = errno_back;
}
