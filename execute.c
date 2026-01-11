#include "main.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/**
* execute - Forks and executes a command if found
* @argv0: Shell name
* @argv: Argument array
* @line_number: Current command line number
* Return: Exit status
*/
int execute(char *argv0, char **argv, int line_number)
{
	pid_t pid;
	int status;

	char *cmd_path = find_command_in_path(argv[0]);

	if (!cmd_path)
	{
		fprintf(stderr, "%s: %d: %s: No such file or directory\n",
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
	return ((WIFEXITED(status)) ? WEXITSTATUS(status) : 1);
}
