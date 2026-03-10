#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "shell.h"

// Forward declarations so the table can reference them
static void echo_func(Command cmd);
static void type_func(Command cmd);
static void exit_func(Command cmd);

static builtin_entry BUILTINS[] = {
    {"echo", echo_func},
    {"type", type_func},
    {"exit", exit_func},
    {NULL, NULL}};

int run_builtin(Command cmd)
{
  char *name = cmd.args[0];
  for (int i = 0; BUILTINS[i].name != NULL; i++)
  {
    if (strcmp(name, BUILTINS[i].name) == 0)
    {
      BUILTINS[i].fn(cmd);
      return 1;
    }
  }
  return 0;
}

void echo_func(Command cmd)
{
  if (cmd.argc == 1)
  {
    printf("\n");
    return;
  }
  for (int i = 1; i < cmd.argc; i++)
  {
    printf("%s", cmd.args[i]);
    if (i < cmd.argc - 1)
      printf(" ");
  }
  printf("\n");
}

void type_func(Command cmd)
{
  printf("%s is a builtin\n", cmd.args[0]);
}

void exit_func(Command cmd)
{
  int status = 0;
  if (cmd.argc > 1)
  {
    status = atoi(cmd.args[1]);
  }
  exit(status);
}