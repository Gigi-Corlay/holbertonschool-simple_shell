#include "main.h"
#include <string.h>

/**
 * trim_and_get_command - trims leading spaces and returns first word
 * @line: input line
 * Return: pointer to first command or NULL if empty
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

	return (strtok(trimmed, " \t"));
}
