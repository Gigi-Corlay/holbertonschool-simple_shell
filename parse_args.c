#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
* build_full_path - build full path for a command
* @dir: directory
* @cmd: command name
*
* Return: malloc'ed full path or NULL
*/
char *build_full_path(char *dir, char *cmd)
{
	char *full;

	size_t len;
	int need_slash = 1;

	if (!dir || !cmd)
		return (NULL);

	if (dir[0] == '\0')
		dir = ".";

	if (dir[strlen(dir) - 1] == '/')
		need_slash = 0;

	len = strlen(dir) + strlen(cmd) + (need_slash ? 2 : 1);
	full = malloc(len + 1);
	if (!full)
		return (NULL);

	if (need_slash)
		sprintf(full, "%s/%s", dir, cmd);
	else
		sprintf(full, "%s%s", dir, cmd);

	return (full);
}

/**
* check_token_for_cmd - check if a command exists in a single PATH token
* @cmd: command name
* @token: directory from PATH
*
* Return: full path (malloc'ed) if executable, NULL otherwise
*/
char *check_token_for_cmd(char *cmd, char *token)
{
	char *full = build_full_path(token, cmd);

	if (!full)
		return (NULL);

	if (access(full, X_OK) == 0)
		return (full);

	free(full);
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
	char *path_env, *token, *copy, *full;

	path_env = get_path_from_environ();
	if (!path_env || path_env[0] == '\0')
		return (NULL);

	copy = malloc(strlen(path_env) + 1);
	if (!copy)
		return (NULL);
	strcpy(copy, path_env);

	token = strtok(copy, ":");
	while (token)
	{
		full = check_token_for_cmd(cmd, token);
		if (full)
		{
			free(copy);
			return (full);
		}
		token = strtok(NULL, ":");
	}

	free(copy);
	return (NULL);
}

/**
* parse_args - split a line into arguments
* @line: input line
*
* Return: NULL-terminated array of arguments
*/
char **parse_args(char *line)
{
	char **argv;

	char *token;

	int i = 0;

	if (!line)
		return (NULL);

	/* allouer 64 pointeurs directement */
	argv = malloc(sizeof(char *) * 64);
	if (!argv)
		return (NULL);

	token = strtok(line, " \t\n");
	while (token && i < 63)
	{
		size_t tlen = strlen(token);

		argv[i] = malloc(tlen + 1);
		if (!argv[i])
		{
			for (int j = 0; j < i; j++)

				free(argv[j]);
			free(argv);
			return (NULL);
		}
		strcpy(argv[i], token);
		i++;
		token = strtok(NULL, " \t\n");
	}
	argv[i] = NULL;

	return (argv);
}

/**
* trim_and_get_command - trim leading/trailing spaces and get first word
* @line: input line
*
* Return: pointer to first command, NULL if empty
*/
char *trim_and_get_command(char *line)
{
	char *start, *end;

	if (!line)
		return (NULL);

	start = line;
	while (*start == ' ' || *start == '\t' || *start == '\n')
		start++;

	if (*start == '\0')
		return (NULL);

	end = start + strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t' || *end == '\n'))
	{
		*end = '\0';
		end--;
	}

	return (start);
}
