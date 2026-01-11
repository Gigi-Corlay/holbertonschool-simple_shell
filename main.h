#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

extern char **environ;

/* Core shell */
int shell_loop(void);
int execute_input(char **args);

/* Built-in commands */
int handle_builtin(char **args);
void print_env(char **envp);

/* Input functions */
char *read_line(void);
char **split_line(char *line);
void free_args(char **args);

/* PATH utilities */
char *find_path(char *cmd);

/* Environment utilities */
char *get_env_value(const char *name);

/* Utility functions */
void remove_trailing_newline(char *line);

/* Signal handling */
void sigint_handler(int sig);

#endif /* MAIN_H */
