#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

/* Shell I/O */
void print_prompt(void);
char *read_line(size_t *len);

/* Parsing */
char **parse_args(char *line);
char *trim_and_get_command(char *line);

/* Execution */
int execute(char *argv0, char **argv, int line_number);
char *find_command_in_path(char *cmd);
char *find_full_path(char *command);
char *get_path_from_environ(void);

/* Built-ins */
void handle_env(char **args);

/* Shell loop */
void handle_stdin(char *argv0, int *line_number);
void run_shell(char *argv0);
void process_line(char *argv0, char **args, char *line, int *line_number);

/* Signal handling */
void sigint_handler(int sig);

#endif
