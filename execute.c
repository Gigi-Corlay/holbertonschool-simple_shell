#include "main.h"

/**
 * execute_cmd - Execute command
 * @argv: Argument vector
 */
void execute_cmd(char **argv)
{
	pid_t pid;
	char *cmd;

	cmd = find_path(argv[0]);
	if (!cmd)
	{
		perror(argv[0]);
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		execve(cmd, argv, environ);
		perror("execve");
		exit(1);
	}
	wait(NULL);

	if (cmd != argv[0])
		free(cmd);
}
