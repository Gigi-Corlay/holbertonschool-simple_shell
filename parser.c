#include "main.h"
#include <string.h>

/**
 * split_line - Split line into arguments
 * @line: Input line
 * Return: Array of strings
 */
char **split_line(char *line)
{
	char **argv;
	int i = 0;
	char *token;

	argv = malloc(sizeof(char *) * 64);
	if (!argv)
		return (NULL);

	token = strtok(line, " \t\n");
	while (token)
	{
		argv[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	argv[i] = NULL;

	return (argv);
}
