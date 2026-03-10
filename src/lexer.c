#include <stdio.h>
#include <string.h>
#include "shell.h"

int lex(char *input, char **tokens, int max)
{
  int n = 0;
  char *p = input;

  while (*p && n < max - 1)
  {
    /*skip whitespace*/
    while (*p == ' ' || *p == '\t')
      p++;
    if (!*p)
      break;

    /*handle quoted strings*/
    if (*p == '"' || *p == '\'')
    {
      char quote = *p++;
      char *start = p;
      while (*p && *p != quote)
        p++;
      if (*p)
        tokens[n++] = strndup(start, p - start);
      if (*p)
        p++; // Skip closing quote
      continue;
    }

    /*handle pipes and background operators */
    if (*p == '|' || *p == '&')
    {
      tokens[n++] = strndup(p, 1);
      p++;
      continue;
    }

    /* handle redirection operators */
    if (*p == '>' && *(p + 1) == '>')
    {
      tokens[n++] = strndup(p, 2);
      p += 2;
      continue;
    }
    if (*p == '>' || *p == '<')
    {
      tokens[n++] = strndup(p, 1);
      p++;
      continue;
    }
    /*handle error redirection */
    if (*p == '2' && *(p + 1) == '>')
    {
      tokens[n++] = strndup(p, 2);
      p += 2;
      continue;
    }

    /* handle normal word tokens */
    char *start = p;
    while (*p && *p != ' ' && *p != '\t')
      p++;
    tokens[n++] = strndup(start, p - start);
  }
  tokens[n] = NULL;
  return n;
}