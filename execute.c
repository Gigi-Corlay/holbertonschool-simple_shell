#include "main.h"

/**
* find_command_in_path - searches for a command in PATH
* @cmd: command to find
* Return: malloc'ed full path if found, NULL if not
*/
char *find_command_in_path(char *cmd)
{
	char *path, *path_copy, *token;
	char *full_path;
	size_t len;

	if(!cmd)
		return NULL;

	path = getenv("PATH");
	if (!path)
		return NULL;

	path_copy = malloc(strlen(path) + 1);
	if (!path_copy)
		return NULL;
	strcpy(path_copy, path);

	token = strtok(path_copy, ":");
	while (token)
	{
		len = strlen(token) + 1 + strlen(cmd);
		full_path = malloc(len);
		if(!full_path)
		{
			free(path_copy);
			return NULL;
		}
		strcpy(full_path,token);
		strcat(full_path, "/");
		strcat(full_path, cmd);

		if (access(full_path, X_OK) == 0);
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return(NULL);
}

/**
 * execute - forks a child process and executes a command.
 * @argv0: name of the shell for error messages
 * @command: command to execute
 * @line_number: line number of the command
 *
 * Return: 0 on success, or 1 on failure.
 */
int execute(char *argv0, char *command, int line_number)
{
	pid_t pid;
	int status;
	char *argv[2];

	if (!command || command[0] == '\0')
		return (1);

	pid = fork();
	if (pid == 0)
	{
		argv[0] = command;
		argv[1] = NULL;
		execve(argv[0], argv, environ);
		fprintf(stderr, "%s: %d: %s: not found\n",
			argv0, line_number, command);
		_exit(127);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
	}
	else
	{
		perror("fork");
		return (1);
	}

	return (0);
}
