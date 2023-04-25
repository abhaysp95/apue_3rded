#include <apue.h>
#include <errno.h>
#include <stdio.h>

int main(void) {

	char buf[BUFSIZ];
	/* errno = 0;
	setvbuf(stdin, NULL, _IOFBF, 0);
	if (errno != 0) {
		err_sys("setvbuf error");
	} */
	while (fgets(buf, 0, stdin) != NULL) {
		if (fputs(buf, stdout) == EOF) {
			err_sys("output error");
		}
	}

	if (ferror(stdin)) {
		err_sys("input error");
	}

	return 0;
}
