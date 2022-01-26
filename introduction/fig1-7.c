// reads command from standard input and executes command

#include <apue.h>
#include <sys/wait.h>
#include <unistd.h>

int
main(void)
{
  char buf[MAXLINE] = {'\0'};  // from header
  pid_t pid = 0;
  int status = 0;

  printf("%% ");
  while (fgets(buf, MAXLINE, stdin) != NULL) {
    if (buf[strlen(buf) - 1] == '\n')
      buf[strlen(buf) - 1] = 0;  // replace newline char with null

    if ((pid = fork()) < 0) {
      err_sys("fork error");
    } else if (pid == 0) {  // child
      execlp(buf, buf, (char *)0);
      err_ret("couldn't execute: %s\n", buf);
      exit(127);
    }

    // parent
    if ((pid = waitpid(pid, &status, 0)) < 0)
      err_sys("waitpid error");
    printf("%% ");
  }
  exit(0);
}
