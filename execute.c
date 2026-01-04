#include "main.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

/**
* execute - forks and executes a command
* @argv0: shell name
* @command: command to execute
* @line_number: for errors
*
* Return: exit status
*/
int execute(char *argv0, char *command, int line_number)
{
	pid_t pid;
	int status;

	char *argv[2];

	argv[0] = command;
	argv[1] = NULL;

	if (access(command, X_OK) == -1)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", argv0, line_number, command);
		return (127);
	}

	pid = fork();
	if (pid == -1)
		return (1);

	if (pid == 0)
	{
		execve(command, argv, environ);
		_exit(127);
	}

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	return (1);
}
