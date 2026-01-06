#include "main.h"
#include <stdlib.h>
#include <string.h>

/**
* parse_args - split a line into arguments
* @line: input line
* Return: NULL-terminated array of arguments
*/
char **parse_args(char *line)
{
	char **argv;
	char *token;
	int i = 0;

	if (!line)
		return (NULL);

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

/**
* trim_and_get_command - trim leading spaces and get first word
* @line: input line
* Return: pointer to first command, NULL if empty
*/
char *trim_and_get_command(char *line)
{
	char *trimmed = line;

	if (!line)
		return (NULL);

	while (*trimmed == ' ' || *trimmed == '\t')
		trimmed++;

	if (*trimmed == '\0')
		return (NULL);

	return (strtok(trimmed, " \t"));
}
