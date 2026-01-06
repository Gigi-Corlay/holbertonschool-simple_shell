#include "main.h"
#include <string.h>

/**
* get_path_from_environ - returns the value of PATH from environ
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
* find_command_in_path - searches for a command in PATH
* @cmd: command to find
* Return: malloc'ed full path if found, NULL if not
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
