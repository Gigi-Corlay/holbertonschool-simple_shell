#include "main.h"
#include <stdlib.h>
#include <string.h>

/**
* read_line - Reads a line from standard input
* Return: Pointer to the line, NULL on EOF
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
* @line: Input string
* Return: Array of pointers to arguments (NULL-terminated)
*/
char **parse_args(char *line)
{
	char **argv = malloc(sizeof(char *) * 64);

	char *token;

	int i = 0;

	if (!argv || !line)
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
