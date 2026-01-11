#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * read_line - Read a line from stdin
 *
 * Return: malloc'ed string or NULL
 */
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;

	if (getline(&line, &len, stdin) == -1)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

/**
 * split_line - Split a line into arguments
 * @line: input string
 *
 * Return: malloc'ed array of strings
 */
char **split_line(char *line)
{
	int bufsize = 64, i = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
		return (NULL);

	token = strtok(line, " \t\r\n");
	while (token)
	{
		tokens[i] = malloc(strlen(token) + 1);
		if (!tokens[i])
		{
			free_args(tokens);
			return (NULL);
		}
		strcpy(tokens[i], token);
		i++;
		if (i >= bufsize)
			break;
		token = strtok(NULL, " \t\r\n");
	}
	tokens[i] = NULL;
	return (tokens);
}

/**
 * free_args - Free array of strings
 * @args: array
 */
void free_args(char **args)
{
	int i;

	if (!args)
		return;

	for (i = 0; args[i]; i++)
		free(args[i]);
	free(args);
}
