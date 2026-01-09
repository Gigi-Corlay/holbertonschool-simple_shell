#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

/* Shell main loop */
void run_shell(char *argv0);
void handle_stdin(char *argv0, int *line_number);
void process_line(char *argv0, char *line, int *line_number);
char **parse_args(char *line);
char *read_line(void);
char *trim_and_get_command(char *line);
void print_prompt(void);

/* Built-in commands */
int handle_builtin(char *argv0, char **argv, char *line);

/* Execution */
int execute(char *argv0, char **argv, int line_number);
char *find_command_in_path(char *cmd);

/* Signal handling */
void sigint_handler(int sig);

#endif
