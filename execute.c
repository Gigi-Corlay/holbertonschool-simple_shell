#include "main.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

/**
* execute - Forks and executes a command
* @argv0: Shell name
* @argv: Argument array
* @line_number: Command line number
* Return: Exit status
*/
int execute(char *argv0, char **argv, int line_number)
{
	pid_t pid;
	int status;

	char *cmd_path;

	if (!argv || !argv[0])
		return (1);

	cmd_path = find_command_in_path(argv[0]);
	if (!cmd_path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
				argv0, line_number, argv[0]);
		return (127);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(cmd_path);
		return (1);
	}

	if (pid == 0)
	{
		execve(cmd_path, argv, environ);
		fprintf(stderr, "%s: %d: %s: exec failed\n",
				argv0, line_number, argv[0]);
		free(cmd_path);
		_exit(126);
	}

	waitpid(pid, &status, 0);
	free(cmd_path);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	return (1);
}
