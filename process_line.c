#include "main.h"
#include <stdlib.h>

/**
* process_line - Parses a line into args and executes it
* @argv0: Shell name
* @line: Input line
* @line_number: Pointer to command number
*/
void process_line(char *argv0, char *line, int *line_number)
{
	char **args;

	if (!line)
		return;

	args = parse_args(line);
	if (!args || !args[0])
	{
		free(args);
		return;
	}

	if (!handle_builtin(argv0, args, line))
		execute(argv0, args, *line_number);

	free(args);
}
