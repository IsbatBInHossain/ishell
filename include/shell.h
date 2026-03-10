#pragma once

#define MAX_INPUT 1024
#define MAX_ARGS 32
#define MAX_PIPES 8

/* parsed command */

typedef struct
{
  char *args[MAX_ARGS];
  int argc;
  char *redir_input;  /* <*/
  char *redir_output; /* > */
  char *redir_error;  /* 2> */
  int append;         /* >> */
  int background;     /* & */
} Command;

/* pipeline */
typedef struct
{
  Command commands[MAX_PIPES];
  int num_commands;
} Pipeline;

/* builtin */
typedef void (*builtin_fn)(Command cmd);

typedef struct
{
  const char *name;
  builtin_fn fn;
} builtin_entry;

/* prototypes */
void repl();
int lex(char *, char **, int);
Pipeline parse(char **, int);
int run_builtin(Command);
void apply_redirections(Command);
void execute_command(Command);
void execute_pipeline(Pipeline *);