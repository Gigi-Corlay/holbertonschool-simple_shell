#include "main.h"
#include <string.h>
#include <stdio.h>

/**
 * handle_builtin - Handle built-in commands
 * @args: argument array
 *
 * Return: -1 if exit, 1 if builtin executed, 0 otherwise
 */
int handle_builtin(char **args)
{
	if (strcmp(args[0], "exit") == 0)
		return (-1);

	if (strcmp(args[0], "env") == 0)
	{
		print_env(environ);
		return (1);
	}

	return (0);
}

/**
 * print_env - Print environment variables
 * @envp: environment array
 */
void print_env(char **envp)
{
	int i;

	for (i = 0; envp[i]; i++)
		printf("%s\n", envp[i]);
}
