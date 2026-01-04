#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Declare the environment variable array */
extern char **environ;

/* Function prototypes */
void print_prompt(void);
ssize_t read_command(char **line, size_t *len);

/* Simple Shell 0.1 functions */
int execute(char *argv0, char *command, int line_number);
void run_shell(char *argv0);
char *trim_and_get_command(char *line);

#endif /* MAIN_H */
