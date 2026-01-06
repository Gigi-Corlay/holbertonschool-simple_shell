#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * read_line - reads a line from stdin
 * @len: buffer size
 *
 * Return: pointer to line or NULL on EOF
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
