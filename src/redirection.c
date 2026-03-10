#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "shell.h"

void apply_redirection(Command cmd)
{
  /* stdin redirection */
  if (cmd.redir_input)
  {
    int fd = open(cmd.redir_input, O_RDONLY);
    if (fd < 0)
    {
      perror(cmd.redir_input);
      exit(1);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
  }
  /* stdout redirection */
  if (cmd.redir_output)
  {
    int flags = O_WRONLY | O_CREAT | (cmd.append ? O_APPEND : O_TRUNC);
    int fd = open(cmd.redir_output, flags, 0644);
    if (fd < 0)
    {
      perror(cmd.redir_output);
      exit(1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
  }
  /* stderr redirection */
  if (cmd.redir_error)
  {
    int flags = O_WRONLY | O_CREAT | (cmd.append ? O_APPEND : O_TRUNC);
    int fd = open(cmd.redir_error, flags, 0644);
    if (fd < 0)
    {
      perror(cmd.redir_error);
      exit(1);
    }
    dup2(fd, STDERR_FILENO);
    close(fd);
  }
}