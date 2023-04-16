// modify the file descriptor or file status flag only after fetching and then
// updating and then resetting it. Don't modify it directly as it may turn off
// some flag bits

#include <apue.h>
#include <fcntl.h>

/**
  * @param fd: file descriptor
  * @param flags: file status flags to turn on
  */
void set_fl(int fd, int flags) {
	int val = -1;

	if ((val = fcntl(fd, F_GETFL, 0)) < 0) {
		err_sys("fcntl F_GETFL error");
	}

	val |= flags;  // turn on the new flag bits

	if ((val = fcntl(fd, F_SETFL, val)) < 0) {
		err_sys("fcntl F_SETFL error");
	}
}
