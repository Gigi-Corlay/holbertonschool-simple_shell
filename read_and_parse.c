#include "main.h"
#include <stdlib.h>
#include <string.h>

/**
* read_line - Reads a line from stdin
* Return: Pointer to line (must be freed), or NULL on EOF
*/
char *read_line(void)
{
	char *line = NULL;

	size_t len = 0;
	ssize_t nread;

	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
		free(line);
		return (NULL);
	}

	if (nread > 0 && line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	return (line);
}

/**
* parse_args - Splits a line into arguments
* @line: Input line
* Return: NULL-terminated array of arguments
*/
char **parse_args(char *line)
{
	char **argv;

	int i = 0;

	if (!line)
		return (NULL);

	argv = malloc(sizeof(char *) * 64);
	if (!argv)
		return (NULL);

	argv[i] = strtok(line, " \t");
	while (argv[i] && i < 63)
	{
		i++;
		argv[i] = strtok(NULL, " \t");
	}
	argv[i] = NULL;

	return (argv);
}

/**
* trim_and_get_command - Trims leading spaces and returns first word
* @line: Input line
* Return: Pointer to first command or NULL if empty
*/
char *trim_and_get_command(char *line)
{
	char *trimmed;

	if (!line)
		return (NULL);

	trimmed = line;
	while (*trimmed == ' ' || *trimmed == '\t')
		trimmed++;

	if (*trimmed == '\0')
		return (NULL);

	return (trimmed);
}
