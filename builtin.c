#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/**
 * is_number - Checks if a string is a valid non-negative integer
 * @s: String to check
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
 * handle_builtin - Execute built-in commands (exit, env)
 * @argv0: Shell name (for errors)
 * @argv: Argument array
 * @line: Original input line
 * Return: 1 if built-in executed, 0 otherwise
 */
int handle_builtin(char *argv0, char **argv, char *line)
{
	if (!argv[0])
		return (0);

	if (strcmp(argv[0], "exit") == 0)
		return (builtin_exit(argv0, argv, line));

	if (strcmp(argv[0], "env") == 0)
		return (builtin_env(argv0));

	return (0);
}
