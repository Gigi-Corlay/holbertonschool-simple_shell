#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;
void print_prompt(void);
char *read_line(size_t *len);
char **parse_args(char *line);
int execute(char *argv0, char **argv, int line_number);
void handle_env(char **args);
void handle_stdin(char *argv0, int *line_number);
void run_shell(char *argv0);
char *find_command_in_path(char *cmd);
char *get_path_from_environ(void);
void sigint_handler(int sig);
char *trim_and_get_command(char *line);
void process_line(char *argv0, char **args, char *line, int *line_number);

#endif
