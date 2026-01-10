#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

/* loop */
void shell_loop(void);

/* parser */
char **split_line(char *line);

/* execute */
void execute_cmd(char **argv);

/* path */
char *find_path(char *cmd);

/* builtins */
int handle_builtin(char **argv);

/* utils */
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);

#endif
