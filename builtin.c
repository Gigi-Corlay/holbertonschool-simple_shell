#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/**
* is_number - Checks if a string is a valid non-negative integer
* @s: String to check
*
* Return: 1 if number, 0 otherwise
*/
int is_number(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (s[i])
	{
		if (!isdigit(s[i]))
			return (0);
		i++;
	}

	return (1);
}

/**
* handle_builtin - Execute built-in commands (exit, clear env)
* @argv0: Shell name (for errors)
* @argv: Argument array
* @line: Original input line
*
* Return: 1 if built-in executed, 0 otherwise
*/
int handle_builtin(char *argv0, char **argv, char *line)
{
	int i, status = 0;

	if (!argv[0])
		return (0);

	if (strcmp(argv[0], "exit") == 0)
	{
		if (argv[1])
		{
			if (!is_number(argv[1]))
			{
				fprintf(stderr, "%s: exit: Illegal number: %s\n",
						argv0, argv[1]);
				return (1); /* Ne quitte pas si argument invalide */
			}
			status = atoi(argv[1]);
		}
		free(argv);
		free(line);
		exit(status);
	}

	if (strcmp(argv[0], "env") == 0)
	{
		for (i = 0; environ[i]; i++)
			printf("%s\n", environ[i]);
		return (1);
	}

	return (0);
}
