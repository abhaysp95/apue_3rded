#include <apue.h>
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
	if (argc < 2) {
		err_exit(1, "usage: a.out [file...]");
	}

	struct stat buf;
	char *type;

	for (int i = 0; i < argc; i++) {
		if (lstat(argv[i], &buf) < 0) {
			err_ret("lstat error");
			continue;
		}

		printf("%s: ", argv[i]);
		if (S_ISREG(buf.st_mode)) {
			type = "Regular";
		} else if (S_ISDIR(buf.st_mode)) {
			type = "Directory";
		} else if (S_ISCHR(buf.st_mode)) {
			type = "Character Special file";
		} else if (S_ISBLK(buf.st_mode)) {
			type = "Block file";
		} else if (S_ISFIFO(buf.st_mode)) {
			type = "Fifo file";
		} else if (S_ISLNK(buf.st_mode)) {
			type = "Symlink file";
		} else if (S_ISSOCK(buf.st_mode)) {
			type = "Socket file";
		} else {
			type = "** unknown **";
		}
		printf("%s\n", type);
	}

	return 0;
}
