#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
* run_shell - Main loop of the shell
* @argv0: name of the shell
*/
void run_shell(char *argv0)
{
	char *line = NULL;
	size_t len = 0;
	char *cmd;
	int line_number = 0;
	int interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			print_prompt();

		cmd = handle_input(&line, &len);

		if (!cmd && feof(stdin))
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (!cmd)
			continue;

		line_number++;

		if (strcmp(cmd, "exit") == 0)
			break;

		execute(argv0, cmd, line_number);
	}

	free(line);
}
