#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>

/* External environment */
extern char **environ;

/* ===== Shell main loop ===== */
void run_shell(char *argv0);
void handle_stdin(char *argv0, int *line_number);
void process_line(char *argv0, char *line, int *line_number);
char **parse_args(char *line);
char *read_line(void);
char *trim_and_get_command(char *line);
void print_prompt(void);

/* ===== Built-in commands ===== */
int handle_builtin(char *argv0, char **argv, char *line);
int builtin_exit(char *argv0, char **argv, char *line);
int builtin_env(char *argv0);
int is_number(char *s);

/* ===== Execution ===== */
int execute(char *argv0, char **argv, int line_number);
char *get_command_path(char *argv0, char *cmd);
char *find_command_in_path(char *cmd);
char *handle_slash_cmd(char *cmd);
char *build_fullpath(char *dir, char *cmd);
char *_getenv(const char *name);

/* ===== Utility functions ===== */
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strchr(char *s, char c);

/* ===== Signal handling ===== */
void sigint_handler(int sig);

#endif /* MAIN_H */
