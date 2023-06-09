#include <apue.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int sysclone(const char* cmd) {
	struct sigaction ignoremask, saveintr, savequit;

	ignoremask.sa_handler = SIG_IGN;
	ignoremask.sa_flags = 0;
	sigemptyset(&ignoremask.sa_mask);

	// ignore SIGINT & SIGQUIT
	if (sigaction(SIGINT, &ignoremask, &saveintr) == -1) {
		return -1;
	}
	if (sigaction(SIGQUIT, &ignoremask, &savequit) == -1) {
		return -1;
	}

	// block SIGCHLD so that parent (system()) is not confused whether it's own child terminated
	sigset_t chldmask, savemask;
	sigemptyset(&chldmask);
	sigaddset(&chldmask, SIGCHLD);
	if (sigprocmask(SIG_BLOCK, &chldmask, &savemask) == -1) {
		return -1;
	}

	pid_t pid;
	int status = 0;

	if ((pid = fork()) < 0) {
		status = -1;
	} else if (pid == 0) {  // child
		// handle return and error status if its needed
		// restore signal desposition inside child (from what it was before parent blocked/changed it)
		sigaction(SIGINT, &saveintr, NULL);
		sigaction(SIGQUIT, &savequit, NULL);
		sigprocmask(SIG_SETMASK, &savemask, NULL);

		if (execl("/bin/sh", "sh", "-c", cmd, (char*)NULL) < 0) {
			_exit(127);  // exec error
		}
	} else {
		errno = 0;
		while (waitpid(pid, &status, 0) == -1) {
			// here EINTR is generated when "WNOHANG  was  not  set
			// and an unblocked signal or a SIGCHLD was caught"
			if (errno != EINTR) {
				status = -1;
				break;
			}
		}
	}

	// restore signal desposition and changes in signal mask set
	if (sigaction(SIGINT, &saveintr, NULL) == -1) {
		return -1;
	}
	if (sigaction(SIGQUIT, &savequit, NULL) == -1) {
		return -1;
	}
	if (sigprocmask(SIG_SETMASK, &savemask, NULL) == -1) {
		return -1;
	}

	printf("sysclone done\n");
	return status;
}

/** Benefits:
 * No signal is snt to the calling process when we type interrupt or quit
 * character.
 *
 * When the "ed" command exits, SIGCHLD is not sent to the calling
 * process. Instead, it is blocked, until we unblock it in the last call of
 * sigprocmask, after we retrieve child's termination status in system
 * (sysclone) function by calling waitpid
 */
