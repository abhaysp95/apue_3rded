#include <apue.h>
#include <fcntl.h>
#include <unistd.h>

#define SZ 10

int main(int argc, char **argv) {

	if (argc != 2) {
		err_quit("usage: a.out <filename>");
	}

	int fd = -1;
	if ((fd = open(argv[1], O_RDWR | O_APPEND)) < 1) {
		err_sys("file open error");
	}

	// seek to the beginging
	if (lseek(fd, SEEK_SET, 0) < 0) {  // go to begining
		err_sys("problem in seeking");
	}

	// print the original data to replace
	char buff[SZ] = { '\0' };
	if (read(fd, buff, SZ) < 0) {
		// check errno, if you want more controlled error analysis
		err_sys("problem in read");
	}

	printf("original data: %s\n", buff);

	char *replace_buff = "ABCDEFGHIJ";
	if (write(fd, replace_buff, SZ) != SZ) {
		err_sys("write error");
	}

	return 0;
}
