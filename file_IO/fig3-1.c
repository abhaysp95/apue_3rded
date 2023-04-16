#include <apue.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
	if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1) {
		printf("stdin can't seek\n");
	} else {
		printf("stdin can seek\n");
	}

	return 0;
}
