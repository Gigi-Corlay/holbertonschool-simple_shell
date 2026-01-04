#include "main.h"

/**
* handle_input - Reads a line and returns the first command
* @line: pointer to the input buffer
* @len: pointer to the buffer size
*
* Return: first command or NULL if empty
*/
char *handle_input(char **line, size_t *len)
{
	ssize_t nread;
	char *cmd;

	nread = read_command(line, len);
	if (nread == -1)
		return (NULL);

	if (nread <= 1)
		return (NULL);

	if ((*line)[nread - 1] == '\n')
		(*line)[nread - 1] = '\0';

	cmd = trim_and_get_command(*line);
	return (cmd);
}
