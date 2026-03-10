#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"

int main()
{
  repl();
  return 0;
}

void repl()
{
  char input[MAX_INPUT];
  char *tokens[MAX_ARGS * MAX_PIPES];

  while (1)
  {
    printf("ish $ ");
    fflush(stdout);

    if (fgets(input, sizeof(input), stdin) == NULL)
    {
      printf("\n");
      break;
    }

    input[strcspn(input, "\n")] = '\0'; // Replace the trailing newline
    if (input[0] == '\0')
    {
      continue;
    }

    int n_token = lex(input, tokens, MAX_ARGS + MAX_PIPES);
    Pipeline pipeline = parse(tokens, n_token);
    }
}