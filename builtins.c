#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/**
* handle_builtin - Executes exit and env built-ins
* @argv: Argument array
* @line: Original input line
* Return: 1 if executed, 0 otherwise
*/
int handle_builtin(char **argv, char *line)
{
	int i;

	if (_strcmp(argv[0], "exit") == 0)
	{
		free(line);
		free(argv);
		exit(0);
	}

	if (_strcmp(argv[0], "env") == 0)
	{
		for (i = 0; environ[i]; i++)
			printf("%s\n", environ[i]);
		return (1);
	}

	return (0);
}
