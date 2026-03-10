#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "shell.h"

void execute_pipeline(Pipeline *p)
{
  int n = p->num_commands;
  if (n == 1)
  {
    execute_command(p->commands[0]);
    return;
  }
  int pipes[MAX_PIPES][2];
  pid_t pids[MAX_PIPES];

  for (int i = 0; i < n - 1; i++)
  {
    if (pipe(pipes[i]) < 0)
    {
      perror("failed to create the pipe");
      exit(1);
    }
  }

  for (int i = 0; i < n; i++)
  {
    pids[i] = fork();
    if (pids[i] < 0)
    {
      perror("fork failed");
      exit(1);
    }
    if (pids[i] == 0)
    {
      /* read from stdin if not the first cmd in pipeline*/
      if (i > 0)
        dup2(pipes[i - 1][0], STDIN_FILENO);

      /*write to the next pipe if not the last cmd in pipeline */
      if (i < n - 1)
        dup2(pipes[i][1], STDOUT_FILENO);

      /* close the pipes in child */
      for (int j = 0; j < n - 1; j++)
      {
        close(pipes[j][0]);
        close(pipes[j][1]);
      }

      Command *cmd = &p->commands[i];
      apply_redirections(*cmd);
      cmd->args[cmd->argc] = NULL;
      execvp(cmd->args[0], cmd->args);
      perror(cmd->args[0]);
      exit(127);
    }
  }
  /* parent closes all pipes and waits for all children */
  for (int i = 0; i < n - 1; i++)
  {
    close(pipes[i][0]);
    close(pipes[i][1]);
  }
  for (int i = 0; i < n; i++)
    waitpid(pids[i], NULL, 0);
}