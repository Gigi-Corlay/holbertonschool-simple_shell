#include "main.h"
#include <string.h>
#include <stdlib.h>

/**
 * run_shell - Main loop of the shell
 * @argv0: name of the shell (for error messages)
 */
void run_shell(char *argv0)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int interactive = isatty(STDIN_FILENO) && isatty(STDOUT_FILENO);
	int line_number = 0;
	char *cmd;

	while (1)
	{
		if (interactive)
			print_prompt();

		nread = read_command(&line, &len);
		if (nread == -1) /* Ctrl+D */
		{
			if (interactive)
				write(1, "\n", 1);
			break;
		}
		if (nread <= 1) /* Empty line */
			continue;

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		cmd = trim_and_get_command(line);
		if (!cmd)
			continue;

		line_number++;

		if (strcmp(cmd, "exit") == 0)
		{
			free(line);
			exit(0);
		}

		/* Execute only the first word */
		if (execute(argv0, cmd, line_number) != 0)
			fprintf(stderr, "%s: %d: %s: not found\n", argv0, line_number, cmd);
	}

	free(line);
}
