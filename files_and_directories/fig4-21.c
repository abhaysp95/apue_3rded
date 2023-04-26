#include <apue.h>
#include <bits/types/struct_timespec.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
	/* for (int i = 1; i < argc; i++) {
		if (open(argv[i], O_RDWR | O_TRUNC) < 0) {  // modifies both last-modification time and change time (not access time)
			err_sys("open error: %s", argv[i]);
		}
	} */
	// to only modify change time
	// store the previous access time and modification time and reset it back after doing operation on file

	struct stat statbuf;
	struct timespec times[2];

	for (int i = 1; i < argc; i++) {
		if (lstat(argv[1], &statbuf) < 0) {
			err_ret("%s: stat error", argv[1]);
			continue;
		}
		int fd = -1;
		if ((fd = open(argv[1], O_RDWR | O_TRUNC)) < 0) {
			err_ret("%s: open error", argv[1]);
			continue;
		}
		times[0] = statbuf.st_atim;  // fill the already recorded time to this timespec buf
		times[1] = statbuf.st_mtim;
		if (futimens(fd, times) < 0) {
			err_ret("%s: futimens error", argv[i]);
		}
		close(fd);
	}

	exit(0);
}
