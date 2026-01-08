#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

/* Shell loop */
void run_shell(char *argv0);
void handle_stdin(char *argv0, int *line_number);
void process_line(char *argv0, char **args, char *line, int *line_number);

/* Built-ins */
int handle_cd(char **args);
int handle_exit(char **args, char *line, char *argv0, int *line_number);
void handle_env(char **args);
int handle_builtin(char *argv0, char **args, char *line, int *line_number);
int handle_pwd(void);

/* Execution */
int execute(char *argv0, char **argv, int line_number);
char *find_command_in_path(char *cmd);
char *get_path_from_environ(void);

/* Parsing */
char **parse_args(char *line);
char *trim_and_get_command(char *line);
char *check_token_for_cmd(char *cmd, char *token);

/* Shell I/O */
void print_prompt(void);
char *read_line(size_t *len);
void process_input_line(char *argv0, char *line, int *line_number);

/* Signal handling */
void sigint_handler(int sig);

#endif /* MAIN_H */
