#include <apue.h>
#include <stdio.h>

int main(void) {

	char buf[BUFSIZ];
	while (fgets(buf, BUFSIZ, stdin) != NULL) {
		if (fputs(buf, stdout) == EOF) {
			err_sys("output error");
		}
	}

	if (ferror(stdin)) {
		err_sys("input error");
	}

	return 0;
}
