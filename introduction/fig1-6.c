// print its process ID

#include <apue.h>
#include <unistd.h>

int
main(void)
{
  printf("Hello World from process ID: %ld\n", (long)getpid());
  exit(0);
}
