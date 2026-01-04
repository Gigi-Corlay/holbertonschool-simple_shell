#include "main.h"
#include <string.h>

/**
* print_prompt - Displays the shell prompt
*/
void print_prompt(void)
{
	write(1, "$ ", 2);
}

/**
* read_command - Reads a line from standard input
* @line: pointer to the buffer to store input
* @len: pointer to the size of the buffer
* Return: number of characters read, -1 on EOF
*/
ssize_t read_command(char **line, size_t *len)
{
	ssize_t nread;

	nread = getline(line, len, stdin);
	if (nread == -1)
		return (-1);

	return (nread);
}
