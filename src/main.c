#include <stdio.h>
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
    printf("%s", input);
  }
}