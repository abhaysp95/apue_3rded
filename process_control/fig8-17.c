#include <apue.h>
#include <stdio.h>

// I just copied the executable of this program to some path in my HOME
// directory which is in PATH with the name "echoall"

int main(int argc, char **argv) {
	char **ptr;
	extern char **environ;

	// echo all command-line args
	for (size_t i = 0; i < argc; i++) {
		printf("argv[%zu]: %s\n", i, argv[i]);
	}

	// give all env strings
	for (ptr = environ; *ptr != 0; ptr++) {
		printf("%s\n", *ptr);
	}

	exit(0);
}
