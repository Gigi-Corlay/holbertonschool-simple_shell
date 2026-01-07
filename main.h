#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

/* Environment variable pointer */
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
char *build_full_path(char *dir, char *cmd);
char *get_path_from_environ(void);
int fork_and_execute(char *cmd, char **argv, char *argv0);
char *resolve_command_path(char *argv0, char *cmd, int line_number);

/* Built-ins */
void handle_env(char **args);

/* Shell loop */
void handle_stdin(char *argv0, int *line_number);
void run_shell(char *argv0);
void process_line(char *argv0, char **args, char *line, int *line_number);

/* Signal handling */
void sigint_handler(int sig);

/* Exit built-in */
int handle_exit(char **args, char *line, char *argv0, int *line_number);
int handle_cd(char **args);
#endif
