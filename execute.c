#include "main.h"
#include <sys/wait.h>

/**
 * execute - forks a child and executes a command
 * @argv0: name of the shell
 * @command: command to execute
 * @line_number: line number for error messages
 * Return: exit status of the command
 */
int execute(char *argv0, char *command, int line_number)
{
	pid_t pid;
	char *argv[2];
	int status;

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
