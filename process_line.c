#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

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
 * handle_cd - changes the current working directory
 * @args: array of arguments passed to the cd command
 *
 * Return: 0 on success, 1 on failure
 */
int handle_cd(char **args)
{
	char *path;

	if (args[1] == NULL)
	{
		path = getenv("HOME");
		if (!path)
		{
			perror("cd");
			return (1);
		}
	}
	else
	{
		path = args[1];
	}

	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}

	return (0);
}

/**
* process_line - processes a single command line
* @argv0: shell name
* @args: parsed arguments
* @line: original line
* @line_number: pointer to line counter
*/
void process_line(char *argv0, char **args, char *line, int *line_number)
{
	if (!args || !args[0])
		return;

	if (strcmp(args[0], "exit") == 0)
	{
		handle_exit(args, line, argv0, line_number);
		return;
	}
	if (strcmp(args[0], "cd") == 0)
	{
		handle_cd(args);
		free(args);
		free(line);
		return;
	}

	if (strcmp(args[0], "env") == 0)
	{
		handle_env(args);
		free(args);
		free(line);
		return;
	}

	execute(argv0, args, *line_number);
	free(args);
	free(line);
}
