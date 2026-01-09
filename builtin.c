#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
* handle_builtin - Execute built-in commands (exit, env)
* @argv0: Shell name (for errors)
* @argv: Argument array
* @line: Original input line
* Return: 1 if built-in executed, 0 otherwise
*/
int handle_builtin(char *argv0, char **argv, char *line)
{
	int i;
	(void)argv0;
	if (!argv[0])
		return (0);

	if (strcmp(argv[0], "exit") == 0)
	{
		free(argv);
		free(line);
		exit(0);
	}

	if (strcmp(argv[0], "env") == 0)
	{
		for (i = 0; environ[i]; i++)
			printf("%s\n", environ[i]);
		return (1);
	}

	return (0);
}
