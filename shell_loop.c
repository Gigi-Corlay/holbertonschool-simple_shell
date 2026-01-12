#include "main.h"
#include <stdlib.h>
#include <unistd.h>

/**
* run_shell - Main shell loop
* @argv0: Shell name (for errors)
*/
void run_shell(char *argv0)
{
	int line_number = 0;

	handle_stdin(argv0, &line_number);
}

/**
* handle_stdin - Reads input lines and executes them
* @argv0: Shell name
* @line_number: Pointer to line counter
*/
void handle_stdin(char *argv0, int *line_number)
{
	int interactive = isatty(STDIN_FILENO);

	char *line;
	char *cmd;

	while (1)
	{
		if (interactive)
			print_prompt();

		line = read_line();
		if (!line)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			exit(0);
		}

		(*line_number)++;
		cmd = trim_and_get_command(line);
		if (!cmd)
		{
			free(line);
			continue;
		}

		process_line(argv0, line, line_number);
		free(line);
	}
}
