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
* fork_and_execute - forks and executes a command
* @cmd: full path to the executable
* @argv: arguments array
* @argv0: shell name
*
* Return: exit status of the child process
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
* resolve_command_path - returns the full path of a command
* @argv0: shell name (used for error messages)
* @cmd: command to execute
* @line_number: command line number
*
* Return: malloc'ed full path or NULL if not found
*/
char *resolve_command_path(char *argv0, char *cmd, int line_number)
{
	char *full_path;

	if (strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		fprintf(stderr, "%s: %d: %s: not found\n", argv0, line_number, cmd);
		return (NULL);
	}

	full_path = find_command_in_path(cmd);
	if (!full_path || access(full_path, X_OK) != 0)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", argv0, line_number, cmd);
		if (full_path)
			free(full_path);
		return (NULL);
	}

	return (full_path);
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
	char *cmd_path;

	int status;

	if (!argv || !argv[0])
		return (1);

	cmd_path = resolve_command_path(argv0, argv[0], line_number);
	if (!cmd_path)
		return (127);

	status = fork_and_execute(cmd_path, argv, argv0);

	if (cmd_path != argv[0])
		free(cmd_path);

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
