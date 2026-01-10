#include "main.h"

/**
 * handle_builtin - Handle built-in commands
 * @argv: Argument vector
 * Return: 1 if builtin handled, 0 otherwise
 */
int handle_builtin(char **argv)
{
	int i;

	if (_strcmp(argv[0], "exit") == 0)
		exit(0);

	if (_strcmp(argv[0], "env") == 0)
	{
		for (i = 0; environ[i]; i++)
			printf("%s\n", environ[i]);
		return (1);
	}
	return (0);
}
