// copy STDIN to STDOUT

#include <apue.h>
#include <unistd.h>

#define BUFSIZE 4096

int main(void) {
	char buf[BUFSIZE];

	ssize_t n = -1;
	if ((n = read(STDIN_FILENO, &buf, BUFSIZE)) > 0) {
		if (write(STDOUT_FILENO, buf, n) != n) {
			err_sys("write error");
		}
	}

	if (n < 0) {
		err_sys("read error");
	}

	return 0;
}
