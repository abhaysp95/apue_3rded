// shows the use of two error function strerror and perror

#include <apue.h>
#include <errno.h>

int
main(int argc, char **argv)
{
  fprintf(stderr, "EACCES: %s\n", strerror(EACCES));
  errno = ENOENT;
  perror(argv[0]);
  exit(0);
}
