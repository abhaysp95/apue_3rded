// create a file with hole

#include <apue.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

const char *buf1 = "abcdefghij";
const char *buf2 = "ABCDEFGHIJ";

int main(void) {
	int fd = -1;
	if ((fd = open("file_hole.txt", O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) == -1) {
		err_sys("Can't open/create file \"file_hole.txt\"\n");
	}

	ssize_t n = -1;
	if ((n = write(fd, buf1, 10)) != 10) {
		err_sys("buf1 write error");
	}

	// seek by some offset
	if (lseek(fd, 16000, SEEK_CUR) == -1) {
		err_sys("error in lseek\n");
	}

	if (write(fd, buf2, 10) != 10) {
		err_sys("buf2 write error\n");
	}

	return 0;
}
