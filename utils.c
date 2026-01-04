#include "main.h"
#include <string.h>

/**
* trim_and_get_command - Trim leading spaces and return the first word
* @line: input line
* Return: pointer to the first command or NULL if line is empty
*/
char *trim_and_get_command(char *line)
{
	char *trimmed = line;

	char *cmd;

	/* Skip leading spaces and tabs */
	while (*trimmed == ' ' || *trimmed == '\t')
		trimmed++;

	/* Return NULL if line is empty */
	if (*trimmed == '\0')
		return (NULL);

	/* Find the first word */
	cmd = trimmed;
	while (*trimmed != '\0' && *trimmed != ' ' && *trimmed != '\t')
		trimmed++;

	/* Terminate the first word */
	if (*trimmed != '\0')
		*trimmed = '\0';

	return (cmd);
}
