#include "main.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
* get_path_from_environ - get the PATH variable from environment
* Return: pointer to PATH string, NULL if not found
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
* find_command_in_path - search for a command in PATH directories
* @cmd: command to search
* Return: malloc'ed full path if found, NULL otherwise
*/
char *find_command_in_path(char *cmd)
{
	char *path, *path_copy, *token, *full_path;

	size_t len;

	path = get_path_from_environ();
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	token = strtok(path_copy, ":");
	while (token)
	{
		len = strlen(token) + strlen(cmd) + 2;
		full_path = malloc(len);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		strcpy(full_path, token);
		strcat(full_path, "/");
		strcat(full_path, cmd);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
* execute - fork a child process and execute a command
* @argv0: shell name (for error messages)
* @argv: array of arguments (command + options)
* @line_number: line counter
* Return: 0 if success, 1 if failure
*/
int execute(char *argv0, char **argv, int line_number)
{
	pid_t pid;
	int status;

	char *cmd_path;

	if (!argv || !argv[0])
		return (1);

	if (strchr(argv[0], '/'))
		cmd_path = argv[0];
	else
		cmd_path = find_command_in_path(argv[0]);

	if (!cmd_path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
				argv0, line_number, argv[0]);
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

/**
* handle_env - print all environment variables
* @args: arguments (unused)
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
