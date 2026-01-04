#include "main.h"
#include <string.h>

/**
 * run_shell - main loop of the shell
 * @argv0: name of the shell (used for errors)
 */
void run_shell(char *argv0)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int interactive = isatty(STDIN_FILENO);
	int line_number = 0;
	char *cmd;

	while (1)
	{
		if (interactive)
			print_prompt();

		nread = read_command(&line, &len);
		if (nread == -1)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (nread <= 1)
			continue;

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		cmd = trim_and_get_command(line);
		if (!cmd)
			continue;

		if (strcmp(cmd, "exit") == 0)
			break;

		line_number++;
		execute(argv0, cmd, line_number);
	}

	free(line);
}
