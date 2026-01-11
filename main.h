#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

extern char **environ;

/* Shell loop */
void run_shell(char *argv0);
void print_prompt(void);
void sigint_handler(int sig);

/* Input / parser */
char *read_line(void);
char **parse_args(char *line);

/* Built-ins */
int handle_builtin(char **argv, char *line);

/* Execution */
int execute(char *argv0, char **argv, int line_number);
char *find_command_in_path(char *cmd);
char *handle_slash_cmd(char *cmd);
char *build_fullpath(char *dir, char *cmd);
char *_getenv(const char *name);

/* Utils */
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _atoi(char *s);

#endif /* MAIN_H */
