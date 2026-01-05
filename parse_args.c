#include <string.h>
#include "main.h"
#include <stdlib.h>

/**
* parse_args - splits a line into arguments
* @line: input line
* Return: NULL-terminated array of arguments
*/
char **parse_args(char *line)
{
	char **argv;

	int i = 0;

	argv = malloc(sizeof(char *) * 64);
	if (!argv)
		return (NULL);

	argv[i] = strtok(line, " \t");
	while (argv[i])
	{
		i++;
		argv[i] = strtok(NULL, " \t");
	}
	return (argv);
}
