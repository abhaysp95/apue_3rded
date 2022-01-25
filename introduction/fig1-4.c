// read from standard input and write to standard output

#include <apue.h>
#include <unistd.h>

#define BUFSIZE 4096

int
main(void)
{
  ssize_t n = 0;
  char buf[BUFSIZE];

  while ((n = read(STDIN_FILENO, buf, BUFSIZE)) > 0)
    if (write(STDOUT_FILENO, buf, n) != n)
      err_sys("write error");

  if (n < 0)
    err_sys("read error");

  exit(0);
}
