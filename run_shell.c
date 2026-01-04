#include "main.h"
#include <string.h>
#include <stdlib.h>

/**
 * run_shell - Main loop of the shell
 * @argv0: name of the shell (for error messages)
 *
 * Return: nothing
 */
void run_shell(char *argv0)
{
	char *line = NULL;

	size_t len = 0;
	char *cmd;

	int line_number = 0;

	int interactive = isatty(STDIN_FILENO) && isatty(STDOUT_FILENO);

	while (1)
	{
		if (interactive)
			print_prompt();

		cmd = handle_input(&line, &len);
		if (!cmd)
			continue;

		line_number++;

		if (strcmp(cmd, "exit") == 0)
		{
			free(line);
			exit(0);
		}

		/* Execute the command */
		execute(argv0, cmd, line_number);
	}

	free(line);
}
