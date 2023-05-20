#include <apue.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
	printf("ruid: %d, euid: %d\n", getuid(), geteuid());
	return 0;
}
