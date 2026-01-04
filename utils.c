#include "main.h"
#include <unistd.h>
#include <stdlib.h>

/**
 * print_prompt - prints the shell prompt
 */
void print_prompt(void)
{
	write(STDOUT_FILENO, "($) ", 4);
}

/**
 * read_command - reads one line from stdin
 * @line: pointer to buffer where line will be stored
 * @len: pointer to size of buffer
 *
 * Return: number of characters read, or -1 on failure/EOF
 */
ssize_t read_command(char **line, size_t *len)
{
	return (getline(line, len, stdin));
}

/**
 * handle_input - reads a line and trims it
 * @line: pointer to buffer where line will be stored
 * @len: pointer to size of buffer
 *
 * Return: pointer to first word of the command, or NULL if empty/EOF
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
 * trim_and_get_command - trims leading spaces and returns first word
 * @line: input line
 *
 * Return: pointer to first word, or NULL if line is empty
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
