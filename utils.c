#include "main.h"

/**
* trim_and_get_command - Trim leading spaces and return the first word
* @line: input line
* Return: pointer to the first command or NULL if line is empty
*/
char *trim_and_get_command(char *line)
{
	char *start = line;

	char *end;

	/* Skip leading spaces and tabs */
	while (*start == ' ' || *start == '\t')
		start++;

	if (*start == '\0')
		return (NULL);

	end = start;
	while (*end != '\0' && *end != ' ' && *end != '\t')
		end++;

	/* Null-terminate the first word */
	if (*end != '\0')
		*end = '\0';

	return (start);
}
