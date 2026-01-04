#include "main.h"

/**
 * execute - Forks a child process and executes a command
 * @argv0: name of the shell (for error messages)
 * @command: command to execute
 * @line_number: line number of the command (for errors)
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
	if (pid == 0)
	{
		argv[0] = command;
		argv[1] = NULL;

		execve(argv[0], argv, environ);

		fprintf(stderr, "%s: %d: %s: not found\n", argv0, line_number, command);
		fflush(stderr);
		_exit(127);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
	{
		perror("fork");
		return (1);
	}

	return (0);
}
