#include <apue.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
	if (open("tmpfile", O_RDWR) < 0) {
		err_sys("open error, create \"tmpfile\" first");
	}
	// open/creat file and the unlink (generally done with operating with
	// temp files). Upon unlinking after opening the file, the file is not
	// deleted as it is open rn, but only when the file is closed or the
	// program terminates
	if (unlink("tmpfile") < 0) {  // can also use remove(), for file it's similar to unlink(), for directory it's similar to rmdir()
		err_sys("unlink error");
	}
	printf("file unlinked\n");
	sleep(15);
	printf("done\n");

	exit(0);
}
