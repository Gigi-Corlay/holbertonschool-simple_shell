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
int execute(char *command);
void run_shell(void);

#endif /* MAIN_H */
