#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
* read_line - read a line from standard input
* @len: pointer to buffer size
* Return: pointer to line (to free), NULL on EOF
*/
char *read_line(size_t *len)
{
	char *line = NULL;

	ssize_t nread;

	nread = getline(&line, len, stdin);
	if (nread == -1)
	{
		free(line);
		return (NULL);
	}

	if (nread > 0 && line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	return (line);
}

/**
* print_prompt - print shell prompt
*/
void print_prompt(void)
{
	write(STDOUT_FILENO, "($) ", 4);
}
