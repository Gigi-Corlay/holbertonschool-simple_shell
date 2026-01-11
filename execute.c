#include "main.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

/**
* handle_slash_cmd - Checks if command with '/' is executable
* @cmd: Command string
* Return: cmd if executable, NULL otherwise
*/
char *handle_slash_cmd(char *cmd)
{
	if (!cmd)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (cmd);
	return (NULL);
}

/**
* build_fullpath - Builds full path from dir and cmd
* @dir: Directory path
* @cmd: Command name
* Return: Full path malloc'ed or NULL
*/
char *build_fullpath(char *dir, char *cmd)
{
	char *full;

	int i = 0, j = 0;

	if (!dir || !cmd)
		return (NULL);

	full = malloc(_strlen(dir) + _strlen(cmd) + 2);
	if (!full)
		return (NULL);

	while (dir[i])
	{
		full[i] = dir[i];
		i++;
	}
	full[i++] = '/';
	while (cmd[j])
		full[i++] = cmd[j++];
	full[i] = '\0';
	return (full);
}

/**
* find_command_in_path - Searches for command in PATH
* @cmd: Command string
* Return: Full path malloc'ed if found, NULL otherwise
*/
char *find_command_in_path(char *cmd)
{
	char *path_env, *path_copy, *dir, *full;

	if (!cmd)
		return (NULL);
	if (_strchr(cmd, '/'))
		return (handle_slash_cmd(cmd));

	path_env = _getenv("PATH");
	if (!path_env)
		return (NULL);

	path_copy = malloc(_strlen(path_env) + 1);
	if (!path_copy)
		return (NULL);
	_strcpy(path_copy, path_env);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		full = build_fullpath(dir, cmd);
		if (full && access(full, X_OK) == 0)
		{
			free(path_copy);
			return (full);
		}
		free(full);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

/**
* execute - Forks and executes a command
* @argv0: Shell name
* @argv: Argument array
* @line_number: Line number
* Return: Exit status of command
*/
int execute(char *argv0, char **argv, int line_number)
{
	pid_t pid;
	int status;

	char *cmd_path;

	cmd_path = find_command_in_path(argv[0]);
	if (!cmd_path)
	{
		fprintf(stderr, "%s: %d: %s: No such file or directory\n",
				argv0, line_number, argv[0]);
		return (127);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(cmd_path);
		return (1);
	}

	if (pid == 0)
	{
		execve(cmd_path, argv, environ);
		fprintf(stderr, "%s: %d: %s: exec failed\n",
				argv0, line_number, argv[0]);
		free(cmd_path);
		_exit(126);
	}

	waitpid(pid, &status, 0);
	free(cmd_path);
	return ((WIFEXITED(status)) ? WEXITSTATUS(status) : 1);
}
