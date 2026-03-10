# ishell

A Unix shell built from scratch in C, as a learning project.

## Platform

Linux only. The shell relies on POSIX APIs (`fork`, `execvp`, `pipe`, `dup2`, `waitpid`) that are not available on Windows, and are not guaranteed on macOS.

## Build

```bash
make
```

Requires `gcc` and `make`. Use `make clean` to remove build artifacts.

## Run

```bash
./ishell
```

## Features

- REPL loop with a prompt
- Builtin commands: `echo`, `exit`, `type`
- Execute any program on the `$PATH`
- I/O redirection: `>`, `>>`, `<`, `2>`
- Piping: `cmd1 | cmd2`
- Multi-command pipelines: `a | b | c`
- Single and double quote parsing
- Background processes with `&`
