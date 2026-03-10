#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "shell.h"

// Forward declarations so the table can reference them
static void echo_func(Command cmnd);
static void type_func(Command cmnd);
static void exit_func(Command cmnd);

static builtin_entry BUILTINS[] = {
    {"echo", echo_func},
    {"type", type_func},
    {"exit", exit_func},
    {NULL, NULL}};

int run_builtin(Command cmnd)
{
  char *name = cmnd.args[0];
  for (int i = 0; BUILTINS[i].name != NULL; i++)
  {
    if (strcmp(name, BUILTINS[i].name) == 0)
    {
      BUILTINS[i].fn(cmnd);
      return 1;
    }
  }
  return 0;
}

void echo_func(Command cmnd)
{
  if (cmnd.argc == 1)
  {
    printf("\n");
    return;
  }
  for (int i = 1; i < cmnd.argc; i++)
  {
    printf("%s", cmnd.args[i]);
    if (i < cmnd.argc - 1)
      printf(" ");
  }
  printf("\n");
}

void type_func(Command cmnd)
{
  printf("%s is a builtin\n", cmnd.args[0]);
}

void exit_func(Command cmnd)
{
  int status = 0;
  if (cmnd.argc > 1)
  {
    status = atoi(cmnd.args[1]);
  }
  exit(status);
}