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
 * fork_and_execute - fork and run command
 * @cmd: full path or argv[0]
 * @argv: arguments
 * @argv0: shell name
 *
 * Return: status code
 */
int fork_and_execute(char *cmd, char **argv, char *argv0)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
	{
		if (token[0] == '\0')  /* PATH vide = répertoire courant */
			token = ".";

		len = strlen(token) + strlen(cmd) + 2;
		full = malloc(len);
		if (!full)
		{
			free(copy);
			return (NULL);
		}

	if (pid == 0)
	{
		execve(cmd, argv, environ);
		perror(argv0);
		_exit(127);
	}

	waitpid(pid, &status, 0);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

/**
 * execute - fork and execute a command
 * @argv0: shell name
 * @argv: arguments array
 * @line_number: command count
 *
 * Return: 0 on success, 1 on failure
 */
int execute(char *argv0, char **argv, int line_number)
{
	char *cmd;
	int status;

	if (!argv || !argv[0])
		return (1);

	cmd = strchr(argv[0], '/') ? argv[0] : find_command_in_path(argv[0]);
	if (!cmd)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			argv0, line_number, argv[0]);
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
