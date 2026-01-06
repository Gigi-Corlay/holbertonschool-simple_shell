#include "main.h"

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
* find_command_in_path - search command in PATH directories
* @cmd: command name
*
* Return: malloc'ed full path or NULL
*/
char *find_command_in_path(char *cmd)
{
	char *path, *copy, *token, *full;

	size_t len;

	if (!cmd)
		return (NULL);

	path = get_path_from_environ();
	if (!path)
		return (NULL);

	copy = strdup(path);
	if (!copy)
		return (NULL);

	token = strtok(copy, ":");
	while (token)
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

		snprintf(full, len, "%s/%s", token, cmd);

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
* execute - fork and execute a command
* @argv0: shell name
* @argv: arguments array
* @line_number: command count
*
* Return: 0 on success, 1 on failure
*/
int execute(char *argv0, char **argv, int line_number)
{
	pid_t pid;
	int status;

	char *cmd;

	if (!argv || !argv[0])
		return (1);

	cmd = strchr(argv[0], '/') ? argv[0] : find_command_in_path(argv[0]);
	if (!cmd)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			argv0, line_number, argv[0]);
		return (127);
	}

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		if (cmd != argv[0])
			free(cmd);
		return (1);
	}

	if (pid == 0)
	{
		execve(cmd, argv, environ);
		perror(argv0);
		_exit(127);
	}

	waitpid(pid, &status, 0);

	if (cmd != argv[0])
		free(cmd);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (1);
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
