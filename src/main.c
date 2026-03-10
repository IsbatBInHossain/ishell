#include <stdio.h>
#include <string.h>
#include "shell.h"

int main()
{
  repl();
  return 0;
}

void repl()
{
  char input[MAX_INPUT];

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

    printf("Input is: %s\n", input);
  }
}