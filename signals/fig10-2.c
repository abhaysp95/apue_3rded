#include <apue.h>
#include <signal.h>
#include <string.h>
#include <features.h>
#include <unistd.h>

static void sig_handler(int);

int main(void) {
	if (signal(SIGUSR1, sig_handler) == SIG_ERR) {  // either returns old sig handler or SIG_ERR
		err_sys("can't reach SIGUSR1");
	}
	if (signal(SIGUSR2, sig_handler) == SIG_ERR) {  // will catch each signal only once (unreliable signal)
		err_sys("can't reach SIGUSR2");
	}

	for (;;) {
		pause();
	}

	exit(0);
}

static void sig_handler(int signo) {

	// reestablish handler again to use it next time
	// signal(signo, sig_handler);  // register whatever signal we just caught again to this same sig handler

	if (signo == SIGUSR1) {
		printf("recieved SIGUSR1\n");
	} else if (signo == SIGUSR2) {
		printf("recieved SIGUSR2\n");
	} else {  // why is this else block necessary ? since this handler will be used only for registered signals, right ?
		char *signame = strdup(strsignal(signo));  // because "The string can be used only
												   // until the next call to strsignal()"
		printf("recieved signal %d [%s]\n", signo, signame);
/* #if defined(__USE_GNU)
		printf("recieved signal %d [%s]\n", signo, sigdescr_np(signo));
#endif */
	}
}
