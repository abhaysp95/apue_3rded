#include <apue.h>
#include <asm-generic/errno-base.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

void make_temp(char *template);

int main(void) {
	char good_template[] = "/tmp/dirXXXXXX";
	char *bad_template = "/tmp/dirXXXXXX";

	printf("trying to create first temp file...\n");
	make_temp(good_template);
	printf("trying to create second temp file...\n");
	make_temp(bad_template);

	exit(0);
}

void make_temp(char *template) {
	int fd = -1;
	struct stat buf;

	if ((fd = mkstemp(template)) < 0) {
		err_sys("can't create temp file: %s", template);
	}
	printf("temp file: %s\n", template);
	close(fd);

	errno = 0;
	if (stat(template, &buf) < 0) {
		if (errno == ENOENT) {
			printf("file doesn't exist\n");
		} else {
			err_sys("stat failed: %s\n", template);
		}
	} else {
		printf("file exists\n");
		unlink(template);
	}
}
