#include <apue.h>
#include <dirent.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef int MyFunc(const char *, const struct stat *, int);

static MyFunc myfunc;
static int doftw(char *, MyFunc *);
static int dopath(MyFunc *);

static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

int main(int argc, char **argv) {
	int ret = 0;

	if (argc != 2) {
		err_quit("usage: a.out <pathname>");
	}

	// basically does every thing for traversal
	ret = doftw(argv[1], myfunc);

	ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
	if (0 == ntot) {
		ntot = 1;  // to avoid divide by 0
	}
	printf("regular files: %7ld, %5.2f %%\n", nreg, nreg * 100.0 / ntot);
	printf("directories : %7ld, %5.2f %%\n", ndir, ndir * 100.0 / ntot);
	printf("block special files: %7ld, %5.2f %%\n", nblk, nblk * 100.0 / ntot);
	printf("char special files: %7ld, %5.2f %%\n", nchr, nchr * 100.0 / ntot);
	printf("FIFO files: %7ld, %5.2f %%\n", nfifo, nfifo * 100.0 / ntot);
	printf("Symbolic link files: %7ld, %5.2f %%\n", nslink, nslink * 100.0 / ntot);
	printf("Socket files: %7ld, %5.2f %%\n", nsock, nsock * 100.0 / ntot);

	exit(ret);
}

static char *fullpath;  // to have fullpath for every file
static size_t pathlen;

static int doftw(char *pathname, MyFunc *func) {
	fullpath = path_alloc(&pathlen);

	if (pathlen <= strlen(pathname)) {
		pathlen = strlen(pathname) * 2;
		if ((fullpath = realloc(fullpath, pathlen)) == NULL) {
			err_sys("realloc failed for make path buffer");
		}
	}
	strcpy(fullpath, pathname);

	return dopath(func);
}

#define FTW_F 1   // file other than directory
#define FTW_D 2   // directory
#define FTW_DNR 3 // directory that can't be read
#define FTW_NS 4  // file that can't stat

// If "fullpath" is anything other than a directory, lstat() it, call func() and
// return. For a directory, call this function (ourself) again for each name in
// directory, basically doing DFS
static int dopath(MyFunc *func) {
	struct stat statbuf;
	struct dirent *dirp;
	DIR *dp;

	if (lstat(fullpath, &statbuf) < 0) {  // stat error
		return func(fullpath, &statbuf, FTW_NS);
	}
	if (S_ISDIR(statbuf.st_mode) == 0) {
		return func(fullpath, &statbuf, FTW_F);
	}

	// it's directory now
	int ret = 0;
	if ((ret = func(fullpath, &statbuf, FTW_D)) != 0) {
		return ret;
	}

	int n = strlen(fullpath);
	if (n + NAME_MAX + 2 > pathlen) {
		pathlen *= 2;
		if ((fullpath = realloc(fullpath, pathlen)) == NULL) {
			err_sys("realloc failed");
		}
	}

	fullpath[n++] = '/';
	fullpath[n] = '\0';

	if ((dp = opendir(fullpath)) == NULL) {  // can't open directory
		return func(fullpath, &statbuf, FTW_DNR);
	}
	while ((dirp = readdir(dp)) != NULL) {
		if (strncmp(dirp->d_name, ".", 1) == 0 ||
			strncmp(dirp->d_name, "..", 2) == 0) {
			continue;  // ignore current and parent dir (dots)
		}
		strcpy(fullpath + n, dirp->d_name);  // append name after '/'
		if ((ret = dopath(func)) != 0) {
			break;  // ttl
		}
	}
	fullpath[n - 1] = 0;  // erase everything from slash onward

	if (closedir(dp) < 0) {
		err_ret("can't close directory: %s", fullpath);
	}

	return ret;
}

static int myfunc(const char *pathname, const struct stat *statptr, int type) {
	switch (type) {
		case FTW_F:
			switch (statptr->st_mode & S_IFMT) {
				case S_IFREG:
					nreg++;
					break;
				case S_IFBLK:
					nblk++;
					break;
				case S_IFCHR:
					nchr++;
					break;
				case S_IFLNK:
					nslink++;
					break;
				case S_IFIFO:
					nfifo++;
					break;
				case S_IFSOCK:
					nsock++;
					break;
				case S_IFDIR:  /* directories should've type = FTW_D */
					err_dump("for S_IFDIR for %s", pathname);
			}
			break;
		case FTW_D:
			ndir++;
			break;
		case FTW_DNR:
			err_ret("can't read directory %s", pathname);
			break;
		case FTW_NS:
			err_ret("stat error for %s", pathname);
			break;
		default:
			err_dump("unkonwn type %d for pathname %s", type, pathname);
	}

	return 0;
}
