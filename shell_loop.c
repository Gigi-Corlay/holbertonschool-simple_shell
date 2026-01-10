#include "main.h"

/**
 * shell_loop - Main shell loop
 */
void shell_loop(void)
{
	char *line = NULL;
	size_t len = 0;
	char **argv;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		if (getline(&line, &len, stdin) == -1)
			break;

		argv = split_line(line);
		if (!argv || !argv[0])
		{
			free(argv);
			continue;
		}

		if (handle_builtin(argv))
		{
			free(argv);
			continue;
		}

		execute_cmd(argv);
		free(argv);
	}
	free(line);
}
