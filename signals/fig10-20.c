#include <apue.h>
#include <signal.h>
#include <stdint.h>
#include <setjmp.h>
#include <time.h>
#include <unistd.h>

static void sig_alarm_handler(int);
static void sig_usr1_handler(int);

static sigjmp_buf env_jmp;
static volatile sig_atomic_t can_jmp;

int main(void) {
	if (signal(SIGUSR1, sig_usr1_handler) == SIG_ERR) {
		err_sys("signal(SIGUSR1) error");
	}
	if (signal(SIGALRM, sig_alarm_handler) == SIG_ERR) {
		err_sys("signal(SIGALRM) error");
	}
	pr_mask("starting main: ");  // fig10-14

	if (sigsetjmp(env_jmp, 1)) {  // came from handler
		pr_mask("ending main: ");
	}
	can_jmp = 1;

	while (1) {
		pause();
	}

	exit(0);
}

static void sig_usr1_handler(int signo) {
	time_t starttime;

	if (can_jmp == 0) return;  // unexpected signal, ignore

	pr_mask("starting sig_usr1_handler: ");

	alarm(3);
	starttime = time(NULL);
	while (1) {
		if (time(NULL) > starttime + 5) {
			break;
		}
	}

	pr_mask("finishing sig_usr1_handler: ");

	can_jmp = 0;
	siglongjmp(env_jmp, 1);
}

static void sig_alarm_handler(int signo) {
	pr_mask("in sig_alarm_handler: ");
}
