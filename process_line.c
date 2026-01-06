#include "main.h"
#include <stdlib.h>
#include <string.h>

/**
* handle_exit - exit the shell
* @args: arguments array
* @line: original input line
* @argv0: shell name (unused)
* @line_number: pointer to line counter (unused)
*
* Return: never returns if exit is called
*/
void handle_exit(char **args, char *line, char *argv0, int *line_number)
{
	(void)argv0;
	(void)line_number;

	if (args && strcmp(args[0], "exit") == 0)
	{
		free(args);
		free(line);
		exit(0);
	}
}

/**
* process_line - process one command line
* @argv0: shell name
* @args: parsed arguments
* @line: original input line
* @line_number: pointer to line counter
*
* Description: checks for builtins 'exit' and 'env',
* or executes external commands if not a builtin.
*/
void process_line(char *argv0, char **args, char *line, int *line_number)
{
	if (!args || !args[0])
		return;

	/* exit builtin */
	handle_exit(args, line, argv0, line_number);

	/* env builtin */
	if (strcmp(args[0], "env") == 0)
	{
		handle_env(args);
		free(args);
		free(line);
		return;
	}

	/* external command */
	execute(argv0, args, *line_number);
	free(args);
	free(line);
}
