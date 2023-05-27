#include <apue.h>
#include <pwd.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

static void alarm_sig_handler(int);

int main(void) {
	struct passwd *ptr;

	signal(SIGALRM, alarm_sig_handler);
	alarm(1);

	for (;;) {
		if ((ptr = getpwnam("raytracer")) == NULL) {
			err_sys("getpwnam() error");
		}
		if (strncmp("raytracer", ptr->pw_name, 9) != 0) {
			err_sys("username not matched, pw_name = %s\n", ptr->pw_name);
		}
	}

	exit(0);
}

static void alarm_sig_handler(int signo) {
	printf("inside alarm signal handler\n");

	struct passwd *rootptr;
	if ((rootptr = getpwnam("root")) != NULL) {
		err_sys("getpwnam(root) error");
	}
	alarm(1);
}
