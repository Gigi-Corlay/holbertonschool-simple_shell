#include "main.h"
#include <string.h>

extern char **environ;

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
		fprintf(stderr, "%s: %d: %s: not found\n", argv0, line_number, command);
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

/**
* run_shell - Main loop of the shell
*/
void run_shell(char *argv0)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
    int interactive;
    int line_number;
    char *trimmed;
    char *cmd;

	interactive = isatty(STDIN_FILENO) && isatty(STDOUT_FILENO);
    line_number = 0;

	while (1)
	{
		if (interactive)
			print_prompt();

		nread = read_command(&line, &len);
		if (nread == -1)
		{
			if (interactive)
				write(1, "\n", 1);
			break;
		}

		if (nread <= 1)
			continue;

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		trimmed = line;

        while (*trimmed == ' ' || *trimmed == '\t')
            trimmed++;

        if (*trimmed == '\0')
            continue;

        cmd = strtok(trimmed, " \t");
        if (!cmd)
            continue;

        line_number++;
        execute(argv0, cmd, line_number);
	}

	free(line);
}
