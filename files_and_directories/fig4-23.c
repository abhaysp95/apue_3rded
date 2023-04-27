#include <apue.h>
#include <asm-generic/errno-base.h>
#include <errno.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
	int sz = NAME_MAX;
	char *cur_name = (char *)malloc(sz);

	// this is just for trail
	errno = 0;
	while (getcwd(cur_name, sz) == NULL) {
		if (errno == ERANGE) {
			sz *= 2;
			if ((cur_name = realloc(cur_name, sz)) == NULL) {
				err_sys("realloc error");
			}
			continue;
		}
		err_dump("can't get current directory");
	}

	printf("current dir: %s\n", cur_name);

	if (chdir("/tmp") < 0) {
		err_sys("chdir error");
	}

	if (getcwd(cur_name, sz) == NULL) {
		err_sys("getcwd error");
	}
	printf("chdir to %s successful\n", cur_name);

	exit(0);
}
