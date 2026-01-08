#include "main.h"
#include <stdlib.h>
#include <unistd.h>

/**
* process_input_line - process a single line of input
* @argv0: shell name (for error messages)
* @line: the input line
* @line_number: pointer to current command number
*
* This function parses the line, executes the command, and frees memory.
*/
void process_input_line(char *argv0, char *line, int *line_number)
{
	char **args = parse_args(line);

	if (!args || !args[0])
	{
		free(args);
		free(line);
		return;
	}

	process_line(argv0, args, line, line_number);

	free(args);
	free(line);
}

/**
* handle_stdin - main shell loop, read and process lines
* @argv0: shell name (for error messages)
* @line_number: pointer to command counter
*
* Reads lines from standard input and executes commands.
*/
void handle_stdin(char *argv0, int *line_number)
{
	int interactive = isatty(STDIN_FILENO);

	size_t len = 0;
	char *line;

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

		process_input_line(argv0, line, line_number);
	}

	if (interactive)
		write(STDOUT_FILENO, "\n", 1);

	exit(0);
}

/**
* run_shell - entry point for shell
* @argv0: shell name
*
* Initializes the shell loop.
*/
void run_shell(char *argv0)
{
	int line_number = 0;

	handle_stdin(argv0, &line_number);
}
