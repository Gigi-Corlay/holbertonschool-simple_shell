#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
* get_path_from_environ - get PATH environment variable
*
* Return: pointer to PATH string, or NULL if not found
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
* @cmd: full path to executable
* @argv: arguments array
* @argv0: shell name (used in error messages)
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
		perror(argv[0]);
		_exit(127);
	}

	waitpid(pid, &status, 0);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	return (1);
}

/**
* resolve_command_path - returns the full path of a command
* @argv0: shell name (used in error messages)
* @cmd: command to execute
* @line_number: line number (used in error messages)
*
* Return: malloc'ed path string or NULL if not found
*/
char *resolve_command_path(char *argv0, char *cmd, int line_number)
{
	char *full_path;

	if (!cmd || cmd[0] == '\0')
		return (NULL);

	if (strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
		{
			full_path = malloc(strlen(cmd) + 1);
			if (!full_path)
				return (NULL);
			sprintf(full_path, "%s", cmd);
			return (full_path);
		}
		fprintf(stderr, "%s: %d: %s: not found\n", argv0, line_number, cmd);
		return (NULL);
	}

	full_path = find_command_in_path(cmd);
	if (!full_path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", argv0, line_number, cmd);
		return (NULL);
	}

	return (full_path);
}

/**
* execute - executes a command
* @argv0: shell name
* @argv: arguments array
* @line_number: current line number
*
* Return: exit status of the command
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

	free(cmd_path);

	return (status);
}

/**
* handle_env - prints all environment variables
* @args: unused
*/
void handle_env(char **args)
{
	int i = 0;

	(void)args;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
