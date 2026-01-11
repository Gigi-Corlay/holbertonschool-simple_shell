#include "main.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
* handle_stdin - main shell loop, read and process lines
* @argv0: shell name (for error messages)
* @line_number: pointer to command counter
*/
void handle_stdin(char *argv0, int *line_number)
{
	int interactive = isatty(STDIN_FILENO);

	size_t len = 0;
	char *line;

	char **args;

	while (1)
	{
		if (interactive)
			print_prompt();

		line = read_line(&len);
		if (!line)
			break;

		(*line_number)++;
		if (line[0] == '\0')
		{
			free(line);
			continue;
		}

		args = parse_args(line);
		if (!args || !args[0])
		{
			free(args);
			free(line);
			continue;
		}

		process_line(argv0, args, line, line_number);
	}

	if (interactive)
		write(STDOUT_FILENO, "\n", 1);

	exit(0);
}

/**
* run_shell - entry point for shell
* @argv0: shell name
*/
void run_shell(char *argv0)
{
	int line_number = 0;

	handle_stdin(argv0, &line_number);
}
