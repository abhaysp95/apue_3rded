#include <apue.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {

	int c = 0;
	while ((c = fgetc(stdin)) != EOF) {
		if(fputc(c, stdout) == EOF) {
			err_sys("output error");
		}
	}

	if (ferror(stdin)) {
		err_sys("input error");
	}

	return 0;
}
