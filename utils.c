#include "main.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
* print_prompt - displays the shell prompt
*/
void print_prompt(void)
{
	write(STDOUT_FILENO, "($) ", 4);
}

/**
* read_command - reads a line from stdin
* @line: buffer
* @len: buffer size
* Return: number of characters read or -1
*/
ssize_t read_command(char **line, size_t *len)
{
	return (getline(line, len, stdin));
}

/**
* handle_input - cleans input and returns first word
* @line: input buffer
* @len: buffer length
* Return: command or NULL
*/
char *handle_input(char **line, size_t *len)
{
	ssize_t nread;
	char *cmd;

	nread = read_command(line, len);
	if (nread == -1)
		return (NULL);

	if (nread > 0 && (*line)[nread - 1] == '\n')
		(*line)[nread - 1] = '\0';

	cmd = trim_and_get_command(*line);
	return (cmd);
}

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

	*end = '\0';
	return (start);
}
