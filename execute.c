#include "main.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
* get_path_from_environ - Returns PATH string from environment
* Return: Pointer to PATH or NULL
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
* find_command_in_path - Searches command in PATH directories
* @cmd: Command to search
* Return: Malloc'ed full path if found, NULL otherwise
*/
char *find_command_in_path(char *cmd)
{
	char *path, *copy, *token, *full;

	size_t len;

	path = get_path_from_environ();
	if (!path)
		return (NULL);

	copy = malloc(strlen(path) + 1);
	if (!copy)
		return (NULL);
	strcpy(copy, path);

	token = strtok(copy, ":");
	while (token)
	{
		len = strlen(token) + strlen(cmd) + 2;
		full = malloc(len);
		if (!full)
		{
			free(copy);
			return (NULL);
		}
		strcpy(full, token);
		strcat(full, "/");
		strcat(full, cmd);

		if (access(full, X_OK) == 0)
		{
			free(copy);
			return (full);
		}
		free(full);
		token = strtok(NULL, ":");
	}

	free(copy);
	return (NULL);
}

/**
* execute - Forks and executes command if it exists
* @argv0: Shell name
* @argv: Argument array
* @line_number: Command number
* Return: 0 on success, 1 on failure
*/
int execute(char *argv0, char **argv, int line_number)
{
	char *cmd_path;

	pid_t pid;
	int status;

	if (!argv || !argv[0])
		return (1);

	if (strchr(argv[0], '/'))
		cmd_path = argv[0];
	else
		cmd_path = find_command_in_path(argv[0]);

	if (!cmd_path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", argv0, line_number, argv[0]);
		return (1);
	}

	pid = fork();
	if (pid == 0)
	{
		execve(cmd_path, argv, environ);
		perror(argv0);
		_exit(127);
	}
	else if (pid < 0)
	{
		perror("fork");
		if (cmd_path != argv[0])
			free(cmd_path);
		return (1);
	}

	waitpid(pid, &status, 0);

	if (cmd_path != argv[0])
		free(cmd_path);

	return (0);
}
