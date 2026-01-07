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
 * fork_and_execute - fork and execute a command
 * @cmd: full path to executable
 * @argv: arguments array
 *
 * Return: exit status of child process
 */
int fork_and_execute(char *cmd, char **argv)
{
	pid_t pid;
	int status;

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
 * resolve_command_path - find full path of command
 * @argv: arguments array
 *
 * Return: malloc'ed path or NULL if not found
 */
char *resolve_command_path(char **argv)
{
	char *cmd;

	if (!argv || !argv[0])
		return (NULL);

	if (strchr(argv[0], '/'))
		cmd = argv[0];
	else
		cmd = find_command_in_path(argv[0]);

	if (!cmd || access(cmd, X_OK) != 0)
	{
		if (cmd && cmd != argv[0])
			free(cmd);
		return (NULL);
	}

	return (cmd);
}

/**
 * execute - execute a command
 * @argv0: shell name
 * @argv: arguments array
 * @line_number: command line number
 *
 * Return: status code
 */
int execute(char *argv0, char **argv, int line_number)
{
	char *cmd;
	int status;

	if (!argv || !argv[0])
		return (1);

	cmd = resolve_command_path(argv);
	if (!cmd)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			argv0, line_number, argv[0]);
		return (127);
	}

	status = fork_and_execute(cmd, argv);

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
