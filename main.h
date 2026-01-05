#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* environment */
extern char **environ;

/* shell functions */
void print_prompt(void);
ssize_t read_command(char **line, size_t *len);
char *trim_and_get_command(char *line);
int execute(char *argv0, char **argv, int line_number);
char **parse_args(char *line);
char *read_line(size_t *len);
void process_line(char *line, char *argv0, int *line_number);
void handle_stdin(char *argv0, int *line_number);
void run_shell(char *argv0);
void sigint_handler(int sig);
int main(int argc, char **argv);
char *find_command_in_path(char *cmd);

#endif
