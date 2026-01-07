#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * get_path_from_environ - get PATH value from environment
 *
 * Return: pointer to PATH value or NULL
 */
char *get_path_from_environ(void)
{
	int i = 0;

	while (environ[i])
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
			return (environ[i] + 5);
		i++;
	}
	return (NULL);
}

/**
 * fork_and_execute - fork and execute a valid command
 * @cmd: full path to executable
 * @argv: arguments array
 * @argv0: shell name
 *
 * Return: exit status of child process
 */
int fork_and_execute(char *cmd, char **argv, char *argv0)
{
	pid_t pid;
	int status;

	(void)argv0;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}

	if (pid == 0)
	{
		execve(cmd, argv, environ);
		_exit(127);
	}

	waitpid(pid, &status, 0);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

/**
 * execute - resolve command path and execute it
 * @argv0: shell name
 * @argv: arguments array
 * @line_number: command count (unused)
 *
 * Return: status code
 */
int execute(char *argv0, char **argv, int line_number)
{
	char *cmd;
	int status;

	(void)line_number; /* suppress unused parameter warning */

	if (!argv || !argv[0])
		return (1);

	cmd = strchr(argv[0], '/') ? argv[0] : find_command_in_path(argv[0]);

	/* Command must exist and be executable BEFORE fork */
	if (!cmd || access(cmd, X_OK) != 0)
	{
		fprintf(stderr, "%s: %s: not found\n", argv0, argv[0]);
		if (cmd && cmd != argv[0])
			free(cmd);
		return (127);
	}

	status = fork_and_execute(cmd, argv, argv0);

	if (cmd != argv[0])
		free(cmd);

	return (status);
}

/**
 * handle_env - print environment variables
 * @args: unused
 */
void handle_env(char **args)
{
	int i = 0;

	(void)args;
	while (environ[i])
		printf("%s\n", environ[i++]);
}
