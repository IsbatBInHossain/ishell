#include <stdio.h>
#include <string.h>
#include "shell.h"

Pipeline parse(char **tokens, int n_token)
{
  Pipeline p;
  memset(&p, 0, sizeof(p));
  p.num_commands = 1;
  Command *cur = &p.commands[0];

  for (int i = 0; i < n_token; i++)
  {
    char *tok = tokens[i];

    if (strcmp(tok, "|") == 0)
    {
      cur = &p.commands[p.num_commands++];
    }
    else if (strcmp(tok, ">") == 0 && i + 1 < n_token)
    {
      cur->redir_output = tokens[++i];
    }
    else if (strcmp(tok, ">>") == 0 && i + 1 < n_token)
    {
      cur->redir_output = tokens[++i];
      cur->append = 1;
    }
    else if (strcmp(tok, "<") == 0 && i + 1 < n_token)
    {
      cur->redir_input = tokens[++i];
    }
    else if (strcmp(tok, "2>") == 0 && i + 1 < n_token)
    {
      cur->redir_error = tokens[++i];
    }
    else if (strcmp(tok, "&") == 0)
    {
      cur->background = 1;
    }
    else
    {
      cur->args[cur->argc++] = tok;
    }
  }
  return p;
}