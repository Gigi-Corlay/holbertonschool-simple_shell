#include "main.h"

/**
 * print_prompt - displays shell prompt
 */
void print_prompt(void)
{
	write(STDOUT_FILENO, "($) ", 4);
}

/**
 * read_command - reads a line from stdin
 * @line: buffer
 * @len: buffer size
 * Return: number of characters read
 */
ssize_t read_command(char **line, size_t *len)
{
	return (getline(line, len, stdin));
}
