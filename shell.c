#include "main.h"

/**
 * print_prompt - Displays the shell prompt
 */
void print_prompt(void)
{
	write(1, "$ ", 2);
}

/**
 * read_command - Reads a line from standard input
 * @line: pointer to the buffer to store input
 * @len: pointer to the size of the buffer
 * Return: number of characters read, -1 on EOF
 */
ssize_t read_command(char **line, size_t *len)
{
	return (getline(line, len, stdin));
}

/**
 * execute - Forks a child process and executes a command
 * @command: the command to execute
 * Return: 0 on success, 1 on failure
 */
int execute(char *command)
{
	pid_t pid;
	int status;
	char *argv[2];

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		return (1);
	}
	else if (pid == 0)
	{
		argv[0] = command;
		argv[1] = NULL;

		execve(argv[0], argv, environ);
		fprintf(stderr, "%s: command not found\n", command);
		_exit(1);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	return (0);
}

/**
 * run_shell - Main loop of the shell
 */
void run_shell(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	while (1)
	{
		print_prompt();

		nread = read_command(&line, &len);
		if (nread == -1)
			break;

		if (nread <= 1)
			continue;

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		execute(line);
	}

	free(line);
}
