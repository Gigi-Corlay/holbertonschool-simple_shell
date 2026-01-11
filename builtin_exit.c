#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * builtin_exit - Handles the exit built-in command
 * @argv0: Shell name (used for error messages)
 * @argv: Argument array
 * @line: Original input line (to free)
 *
 * Return: 1 if handled (but actually exits)
 */
int builtin_exit(char *argv0, char **argv, char *line)
{
	int status = 0;

	if (argv[1])
	{
		if (!is_number(argv[1]))
		{
			fprintf(stderr, "%s: exit: Illegal number: %s\n",
					argv0, argv[1]);
			return (1);  /* don't exit if invalid number */
		}
		status = atoi(argv[1]);
	}

	free(argv);
	free(line);
	exit(status);
}
