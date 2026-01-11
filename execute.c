#include "main.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

/**
 * execute_input - Execute a command
 * @args: argument array
 *
 * Return: 1 to continue, -1 to exit
 */
int execute_input(char **args)
{
	pid_t pid;
	int status;
	int builtin_status;
	char *path;

	if (!args || !args[0])
		return (1);

	builtin_status = handle_builtin(args);
	if (builtin_status != 0)
		return (builtin_status);

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		path = find_path(args[0]);
		if (!path)
		{
			fprintf(stderr, "%s: command not found\n", args[0]);
			exit(127);
		}
		execve(path, args, environ);
		perror("execve");
		free(path);
		exit(1);
	}
	else if (pid > 0)
		wait(&status);
	else
		perror("fork");

	return (1);
}
