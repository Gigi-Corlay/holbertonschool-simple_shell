#include "main.h"
#include <string.h>

/**
* trim_and_get_command - Trim spaces and get first word
* @line: input line
* Return: first command or NULL
*/
char *trim_and_get_command(char *line)
{
	char *trimmed = line;

	while (*trimmed == ' ' || *trimmed == '\t')
		trimmed++;

	if (*trimmed == '\0')
		return (NULL);

	return (trimmed);
}
