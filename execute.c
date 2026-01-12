#include "main.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

/**
* get_command_path - Returns the full path of a command
* @argv0: Shell name
* @cmd: Command name
* Return: malloc'ed path if found, NULL otherwise
*/
char *get_command_path(char *argv0, char *cmd)
{
	char *cmd_path;

	if (!cmd)
		return (NULL);

	if (_strchr(cmd, '/'))
		cmd_path = handle_slash_cmd(cmd);
	else
		cmd_path = find_command_in_path(cmd);

	if (!cmd_path)
		fprintf(stderr, "%s: command not found: %s\n", argv0, cmd);

	return (cmd_path);
}

/**
* execute - Forks and executes a command
* @argv0: Shell name
* @argv: Argument array
* @line_number: Command line number
* Return: Exit status of the command
*/
int execute(char *argv0, char **argv, int line_number)
{
	char *cmd_path;

	pid_t pid;
	int status;

	(void)line_number;

	if (!argv || !argv[0])
		return (1);

	cmd_path = get_command_path(argv0, argv[0]);
	if (!cmd_path)
		return (127);

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		if (cmd_path != argv[0])
			free(cmd_path);
		return (1);
	}

	if (pid == 0) /* child */
	{
		execve(cmd_path, argv, environ);
		perror(argv0);
		_exit(126);
	}

	waitpid(pid, &status, 0);

	if (cmd_path != argv[0])
		free(cmd_path);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	return (1);
}

