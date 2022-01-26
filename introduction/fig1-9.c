// prints user-id and group-id

#include <apue.h>
#include <unistd.h>

int
main(void)
{
  printf("uid = %d, gid = %d\n", getuid(), getgid());
  exit(0);
}
