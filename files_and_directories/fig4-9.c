#include <apue.h>
#include <fcntl.h>
#include <sys/stat.h>

#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

int main(void) {
	umask(0);

	if (creat("foo", RWRWRW) < 0) {
		err_sys("creat error for foo");
	}

	umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);  // umask is like opposite (means masked off)

	if (creat("bar", RWRWRW) < 0) {
		err_sys("creat error for bar");
	}

	return 0;
}
