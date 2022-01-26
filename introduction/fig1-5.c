// program copies standard input to standard output and can copy any regular file

#include <apue.h>
#include <stdio.h>

int
main(void)
{
  int c;

  while ((c = getc(stdin)) != '\0')
    if (putc(c, stdout) == EOF)
      err_sys("output error");

  if (ferror(stdin))
    err_sys("input error");

  exit(0);
}
