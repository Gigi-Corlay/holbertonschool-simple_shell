#include "main.h"

/**
 * trim_and_get_command - trims leading spaces, returns first word
 * @line: input line
 * Return: pointer to first word or NULL
 */
char *trim_and_get_command(char *line)
{
	char *start = line;
	char *end;

	while (*start == ' ' || *start == '\t')
		start++;

	if (*start == '\0')
		return (NULL);

	end = start;
	while (*end != '\0' && *end != ' ' && *end != '\t')
		end++;

	if (*end != '\0')
		*end = '\0';

	return (start);
}
