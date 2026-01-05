#include "main.h"

/**
 * print_prompt - prints the shell prompt
 */
void print_prompt(void)
{
	write(STDOUT_FILENO, "($) ", 4);
}

/**
 * read_command - reads one line from standard input
 * @line: buffer to store input
 * @len: pointer to buffer size
 * Return: number of characters read, -1 on EOF
 */
ssize_t read_command(char **line, size_t *len)
{
	return (getline(line, len, stdin));
}
