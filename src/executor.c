#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "shell.h"

void execute_command(Command cmd)
{
  if (run_builtin(cmd))
  {
    return;
  }
  int pid = fork();
  if (pid < 0)
  {
    perror("fork failed");
    return;
  }
  if (pid == 0)
  {
    /* Child process */
    apply_redirection(cmd);

    cmd.args[cmd.argc] = NULL;
    execvp(cmd.args[0], cmd.args);

    /* execvp only returns on failure */
    perror(cmd.args[0]);
    exit(127);
  }
  /* Parent */
  if (!cmd.background)
  {
    int status;
    waitpid(pid, &status, 0);
    printf("\n");
  }
  else
  {
    printf("[%d] running in background\n", pid);
  }
}