#include <apue.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
	int val = -1;

	if (2 != argc) {
		err_quit("usage: a.out <fd#>");
	}

	if ((val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0) {
		err_sys("fcntl error for fd %d", atoi(argv[1]));
	}

	switch (val & O_ACCMODE) {
		case O_RDONLY:
			printf("read only");
			break;
		case O_WRONLY:
			printf("write only");
			break;
		case O_RDWR:
			printf("read write");
			break;
		default:
			err_dump("unkown access mode");
	}

	if (val & O_APPEND) {
		printf(", append");
	}
	if (val & O_NONBLOCK) {
		printf(", nonblocking");
	}
	if (val & O_SYNC) {
		printf(", synchronous writes");
	}

#if !defined (_POSIX_C_SOURCE) && defined (O_FSYNC) && (O_FSYNC != O_SYNC)
	if (val & O_FSYNC) {
		printf(", synchronous writes");
	}
#endif

	fputc('\n', stdout);
	return 0;
}
