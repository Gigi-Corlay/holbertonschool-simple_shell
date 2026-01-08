#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

/**
* handle_pwd - print the current working directory
*
* Return: 0 on success, 1 on failure
*/
int handle_pwd(void)
{
	char cwd[1024];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("pwd");
		return (1);
	}

	printf("%s\n", cwd);
	return (0);
}

/**
* handle_exit - exits the shell if command is "exit"
* @args: arguments array
* @line: original input line
* @argv0: shell name (unused)
* @line_number: pointer to line counter (unused)
*
* Return: 1 if exit was called, 0 otherwise
*/
int handle_exit(char **args, char *line, char *argv0, int *line_number)
{
	(void)argv0;
	(void)line_number;

	if (strcmp(args[0], "exit") == 0)
	{
		free(args);
		free(line);
		exit(0);
	}

	return (0);
}

/**
* handle_builtin - handle shell built-in commands
* @argv0: shell name (used for error messages)
* @args: arguments array
* @line: original input line
* @line_number: pointer to line counter (used for error messages)
*
* Return: 1 if a built-in was handled, 0 otherwise
*/
int handle_builtin(char *argv0, char **args, char *line, int *line_number)
{
	if (strcmp(args[0], "exit") == 0)
	{
		handle_exit(args, line, argv0, line_number);
		return (1);
	}

	if (strcmp(args[0], "cd") == 0)
	{
		handle_cd(args);
		return (1);
	}

	if (strcmp(args[0], "env") == 0)
	{
		handle_env(args);
		return (1);
	}

	if (strcmp(args[0], "pwd") == 0)
	{
		handle_pwd();
		return (1);
	}

	return (0);
}

/**
* process_line - processes a single command line
* @argv0: name of the shell (used for error messages)
* @args: parsed arguments from the input line
* @line: original input line
* @line_number: pointer to the current line number (used for error messages)
*/
void process_line(char *argv0, char **args, char *line, int *line_number)
{
	if (!args || !args[0])
		return;

	if (handle_builtin(argv0, args, line, line_number))
	{
		free(args);
		free(line);
		return;
	}

	execute(argv0, args, *line_number);
	free(args);
	free(line);
}
