#include "main.h"
#include <stdio.h>

/**
* shell_loop - Main loop of the shell
*
* Return: 0 on normal exit
*/
int shell_loop(void)
{
	char *line;

	char **args;

	int status;

	int eof_count = 0; /* count Ctrl+D */

	while (1)
	{
		printf("$ ");
		fflush(stdout);

		line = read_line();
		if (!line) /* Ctrl+D */
		{
			putchar('\n');
			eof_count++;
			if (eof_count >= 2) /* double Ctrl+D = exit */
				break;
			continue; /* ignore first EOF */
		}
		eof_count = 0;

		args = split_line(line);
		free(line);
		if (!args)
			continue;

		status = execute_input(args);
		free_args(args);

		if (status == -1)
			printf("Le shell a quitté correctement.\n");
				break;
	}

	return (0);
}
