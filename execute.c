#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

/**
 * execute - forks a child and executes a command
 * @argv0: name of the shell (for errors)
 * @command: command to execute
 * @line_number: line number for errors
 * Return: 0 on success, 1 on failure
 */
int execute(char *argv0, char *command, int line_number)
{
	pid_t pid;
	int status;
	char *argv[2];

	if (!command || command[0] == '\0')
		return (1);

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		argv[0] = command;
		argv[1] = NULL;

		execve(argv[0], argv, environ);

		fprintf(stderr, "%s: %d: %s: not found\n", argv0, line_number, command);
		fflush(stderr);
		_exit(127);
	}
	else
	{
		waitpid(pid, &status, 0);
	}

	return (0);
}
