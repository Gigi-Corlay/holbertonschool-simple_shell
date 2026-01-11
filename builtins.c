#include "main.h"
#include <stdlib.h>
#include <stdio.h>

/**
* exit_shell - Frees memory and exits shell
* @line: Input line
* @argv: Argument array
* Return: void (exits)
*/
static void exit_shell(char *line, char **argv)
{
	free(line);
	free(argv);
	exit(0);
}

/**
* print_env - Prints environment variables
* Return: void
*/
static void print_env(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		printf("%s\n", environ[i]);
}

/**
* handle_builtin - Executes built-in commands
* @argv: Argument array
* @line: Input line
* Return: 1 if built-in executed, 0 otherwise
*/
int handle_builtin(char **argv, char *line)
{
	if (_strcmp(argv[0], "exit") == 0)
		exit_shell(line, argv);

	if (_strcmp(argv[0], "env") == 0)
	{
		print_env();
		return (1);
	}

	return (0);
}
