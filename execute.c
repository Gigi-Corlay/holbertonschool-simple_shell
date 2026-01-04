#include "main.h"

/**
 * execute - forks and executes a command
 * @argv0: shell name
 * @command: command to execute
 * @line_number: command line number
 * Return: 0
 */
int execute(char *argv0, char *command, int line_number)
{
	pid_t pid;
	int status;
	char *argv[2];

	pid = fork();
	if (pid == 0)
	{
		argv[0] = command;
		argv[1] = NULL;

		execve(command, argv, environ);

		fprintf(stderr, "%s: %d: %s: not found\n",
			argv0, line_number, command);
		_exit(127);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
	}
	else
	{
		perror("fork");
	}

	return (0);
}
