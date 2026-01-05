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

void run_shell(char *argv0);

int execute(char *argv0, char *command, int line_number);
char *find_command_in_path(char *cmd);

#endif
