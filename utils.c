#include "main.h"
#include <string.h>

/**
 * trim_and_get_command - returns first word of input
 * @line: input line
 * Return: command or NULL
 */
char *trim_and_get_command(char *line)
{
	char *start = line;

	while (*start == ' ' || *start == '\t')
		start++;

	if (*start == '\0')
		return (NULL);

	return (strtok(start, " \t"));
}
