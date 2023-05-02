// dynamically allocate space for pathname

#include <apue.h>
#include <limits.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#ifdef PATH_MAX
static long pathmax = PATH_MAX;
#else
static long pathmax = 0;
#endif

static long posix_version = 0;
static long xsi_version = 0;

// no guarantee for PATH_MAX
#define PATH_MAX_GUESS 1024

char *path_alloc(size_t *sizep) {
	char *ptr;
	size_t size;

	if (0 == posix_version) {
		posix_version = sysconf(_SC_VERSION);
	}

	if (0 == xsi_version) {
		xsi_version = sysconf(_SC_XOPEN_VERSION);
	}

	if (0 == pathmax) {
		errno = 0;
		if ((pathmax = pathconf("/", _PC_PATH_MAX)) < 0) {
			if (0  == errno) {
				pathmax = PATH_MAX_GUESS;  // it's inderterminate
			} else {
				err_sys("pathconf error for _PC_PATH_MAX");
			}
		} else {
			pathmax++;
		}
	}

	// some old history workout
	if ((posix_version < 200112L) && (xsi_version < 4)) {
		size = pathmax + 1; // include null byte too
	} else {
		size = pathmax;  // null byte already included
	}

	if (NULL == (ptr = malloc(size))) {
		err_sys("malloc error for pathname");
	}

	if (NULL != sizep) {
		*sizep = size;
	}

	return ptr;
}

/* int main(void) {  // just for test
	size_t size_p = 0;

	char* pathname_buff = path_alloc(&size_p);
	printf("size allocated: %zu\n", size_p);

	if (NULL != pathname_buff) {
		free(pathname_buff);
	}

	return 0;
} */
