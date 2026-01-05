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
* process_line - parses a line into arguments and executes it
* @line: input line
* @argv0: shell name (for errors)
* @line_number: pointer to current line number
*/
void process_line(char *line, char *argv0, int *line_number)
{
	char **args = parse_args(line);

	if (!args || !args[0])
	{
		free(args);
		return;
	}

	(*line_number)++;
	execute(argv0, args, *line_number);
	free(args);
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

	while (1)
	{
		if (interactive)
			print_prompt();

		line = read_line(&len);
		if (!line) /* EOF */
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

<<<<<<< HEAD
		line_number++;

		if (nread <= 1)
			continue;

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		cmd = trim_and_get_command(line);
		if (!cmd)
			continue;

		if (strcmp(cmd, "exit") == 0)
=======
		if (strcmp(line, "exit") == 0)
		{
			free(line);
>>>>>>> 071a046 (Add support for command arguments in simple_shell)
			break;
		}

<<<<<<< HEAD

		execute(argv0, cmd, line_number);
=======
		process_line(line, argv0, line_number);
		free(line);
>>>>>>> 071a046 (Add support for command arguments in simple_shell)
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
