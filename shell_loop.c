#include "main.h"
#include <stdlib.h>
#include <unistd.h>

/**
* run_shell - Main shell loop
* @argv0: Shell name
*/
void run_shell(char *argv0)
{
	int line_number = 0;

	char *line;

	char **argv;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			print_prompt();

		line = read_line();
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			exit(0);
		}

		line_number++;
		argv = parse_args(line);
		if (!argv || !argv[0])
		{
			free(argv);
			free(line);
			continue;
		}

		if (handle_builtin(argv0, argv, line) == 0)
			execute(argv0, argv, line_number);

		free(argv);
		free(line);
	}
}

/**
* print_prompt - Prints shell prompt
*/
void print_prompt(void)
{
	write(STDOUT_FILENO, "($) ", 4);
}

/**
* sigint_handler - Handles Ctrl+C
* @sig: Signal number
*/
void sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n($) ", 5);
}
