#include "main.h"
#include <unistd.h>
#include <stdlib.h>

/**
* print_prompt - Prints the shell prompt
* Return: void
*/
void print_prompt(void)
{
	write(STDOUT_FILENO, "($) ", 4);
}

/**
* sigint_handler - Handles Ctrl+C (SIGINT)
* @sig: Signal number
* Return: void
*/
void sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n($) ", 5);
}

/**
* process_line - Process a single command line
* @line: Input line
* @argv0: Shell name
* @line_number: Current line number
* Return: void
*/
static void process_line(char *line, char *argv0, int line_number)
{
	char **argv;

	argv = parse_args(line);
	if (!argv || !argv[0])
	{
		free(argv);
		free(line);
		return;
	}

	if (!handle_builtin(argv, line))
		execute(argv0, argv, line_number);

	free(argv);
	free(line);
}

/**
* run_shell - Main shell loop
* @argv0: Name of the shell executable
* Return: void
*/
void run_shell(char *argv0)
{
	int line_number = 0;

	char *line;

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
		process_line(line, argv0, line_number);
	}
}
