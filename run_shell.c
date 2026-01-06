#include "main.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/**
* read_line - reads one line from stdin
* @len: pointer to buffer size (updated by getline)
* Return: pointer to line (must be freed) or NULL on EOF
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
* get_args - parse a line into arguments
* @line: input line
* Return: array of arguments
*/
char **get_args(char *line)
{
	return (parse_args(line));
}

/**
* handle_exit - check for exit command and exit
* @args: array of arguments
* @line: the original line
* Return: 1 if exit was called, 0 otherwise
*/
int handle_exit(char **args)
{
	if (strcmp(args[0], "exit") == 0)
	{
		return (1);
	}
	return (0);
}

/**
* handle_stdin - main loop reading stdin and executing commands
* @argv0: shell name (for errors)
* @line_number: pointer to line counter
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
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			exit(0);
		}

		(*line_number)++;
		if (line[0] == '\0')
		{
			free(line);
			continue;
		}

		args = get_args(line);
		if (args && args[0])
		{
			if (handle_exit(args))
			{
				free(args);
				free(line);
				break;
			}

			execute(argv0, args, *line_number);

			free(args);
		}
		free(line);
	}
}




/**
* run_shell - entry point for shell main loop
* @argv0: shell name (for errors)
*/
void run_shell(char *argv0)
{
	int line_number = 0;

	handle_stdin(argv0, &line_number);
}
