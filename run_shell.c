#include "main.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/**
* run_shell - Main loop of the simple shell
* @argv0: Name of the shell program, used for error messages
*
* Description: This function reads commands from stdin, displays a
* prompt in interactive mode, handles EOF (Ctrl+D), handles the
* "exit" command, and executes simple commands using execve.
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

		if (!cmd && feof(stdin)) /* EOF Ctrl+D */
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (!cmd) /* empty line */
			continue;

		if (strcmp(cmd, "exit") == 0) /* handle exit built-in */
		{
			free(line);
			break;
		}

		line_number++;
		execute(argv0, cmd, line_number);
	}

	free(line);
}
