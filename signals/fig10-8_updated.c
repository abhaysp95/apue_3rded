#include <apue.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>

static unsigned int handler_count = 0;
static sigjmp_buf env_jmp;

static void sig_alarm_handler(int);

unsigned int sleep3(unsigned int sec) {
	struct sigaction act, oact;
	act.sa_handler = sig_alarm_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	if (sigaction(SIGALRM, &act, &oact) < 0) {
		err_sys("sigaction error");
	}

	if (sigsetjmp(env_jmp, 1) == 0) {
		printf("handler count before %d secs: %d\n", sec, handler_count);
		alarm(sec);
		pause();
	}

	printf("handler count before %d secs: %d\n", 3, handler_count);

	alarm(3);
	pause();


	return alarm(0);
}

static void sig_alarm_handler(int signo) {
	handler_count++;
	siglongjmp(env_jmp, 1);
}

int main(void) {
	sleep3(5);
	exit(0);
}
