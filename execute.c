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
 * Return: 0 on success, 1 on failure
 */
int execute(char *argv0, char **argv, int line_number)
{
	pid_t pid;
	int status;

	if (!argv || !argv[0])
		return (1);

	pid = fork();
	if (pid == 0)
	{
		execve(argv[0], argv, environ);
		fprintf(stderr, "%s: %d: %s: not found\n",
			argv0, line_number, argv[0]);
		_exit(127);
	}
	else if (pid < 0)
	{
		perror("fork");
		return (1);
	}

	waitpid(pid, &status, 0);
	return (0);
}
