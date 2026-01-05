#include "main.h"

/**
 * execute - forks a child process and executes a command with arguments
 * @argv0: name of the shell (for error messages)
 * @argv: array of arguments (command + args)
 * @line_number: command count
 *
 * Return: 0 on success, 1 on failure
 */
int execute(char *argv0, char **argv, int line_number)
{
	pid_t pid;
	int status;

	if (!argv || !argv[0])
		return (1);

	pid = fork();
	if (pid == 0)
	{
		execve(argv[0], argv, environ);
		fprintf(stderr, "%s: %d: %s: not found\n",
			argv0, line_number, argv[0]);
		_exit(127);
	}
	else if (pid < 0)
	{
		perror("fork");
		return (1);
	}

	waitpid(pid, &status, 0);
	return (0);
}
