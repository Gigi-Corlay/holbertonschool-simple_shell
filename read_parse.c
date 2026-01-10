#include "main.h"
#include <stdlib.h>
#include <string.h>

/**
 * read_line - Reads a line from stdin
 * Return: Pointer to line (malloc'ed) or NULL on EOF
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
 * parse_args - Splits line into argv array
 * @line: Input line
 * Return: NULL-terminated array
 */
char **parse_args(char *line)
{
	char **argv = malloc(sizeof(char *) * 64);
	char *token;
	int i = 0;

	if (!argv)
		return (NULL);

	token = strtok(line, " \t");
	while (token && i < 63)
	{
		argv[i++] = token;
		token = strtok(NULL, " \t");
	}
	argv[i] = NULL;
	return (argv);
}

/**
 * trim_and_get_command - Returns first word (skip leading spaces)
 * @line: Input line
 * Return: Pointer to first word
 */
char *trim_and_get_command(char *line)
{
	if (!line)
		return (NULL);

	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == '\0')
		return (NULL);

	return (line);
}
