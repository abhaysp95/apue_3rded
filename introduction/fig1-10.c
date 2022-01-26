#include <apue.h>
#include <signal.h>
#include <sys/wait.h>

static void sig_int(int);

int
main(void)
{
  char buf[MAXLINE];
  pid_t pid = 0;
  int status = 0;

  if (signal(SIGINT, sig_int) == SIG_ERR)
    err_sys("signal error");

  printf("%% ");
  while (fgets(buf, MAXLINE, stdin) != NULL) {
    if (buf[strlen(buf) - 1] == '\n')
      buf[strlen(buf) - 1] = 0;

    if ((pid = fork()) < 0) {
      err_sys("fork error");
    } else if (pid == 0) {  // child
      execlp(buf, buf, (char *)NULL);
      err_ret("couldn't execute: %s\n", buf);
      exit(127);
    }

    // parent
    if ((pid = waitpid(pid, &status, 0)) < 0)
      err_sys("waitpid error");
    printf("%% ");
  }
  exit (0);
}

void
sig_int(int signo)
{
  printf("interrupt\n%% ");
}
