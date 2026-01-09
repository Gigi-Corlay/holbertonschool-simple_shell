#include "main.h"
#include <stdlib.h>
#include <string.h>

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

	if (!dir || !cmd)
		return (NULL);

	if (dir[0] == '\0')
		dir = ".";

	len = strlen(dir) + strlen(cmd) + 2;
	full = malloc(len);
	if (!full)
		return (NULL);

	snprintf(full, len, "%s/%s", dir, cmd);
	return (full);
}

/**
 * find_command_in_path - search command in PATH directories
 * @cmd: command name
 *
 * Return: malloc'ed full path or NULL
 */
char *find_command_in_path(char *cmd)
{
	char *path_env, *token;
	char *full;
	char *copy;

	if (!cmd)
		return (NULL);

	path_env = get_path_from_environ();
	if (!path_env)
		return (NULL);

	copy = malloc(strlen(path_env) + 1);
	if (!copy)
		return (NULL);
	strcpy(copy, path_env);  /* autorisé : strcpy */

	token = strtok(copy, ":");
	while (token)
	{
		full = build_full_path(token, cmd);
		if (!full)
		{
			free(copy);
			return (NULL);
		}

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

	/* taille fixe pour les arguments */
	argv = malloc(sizeof(char *) * 64);
	if (!argv)
		return (NULL);

	token = strtok(line, " \t\n");
	while (token && i < 63) /* 63 pour garder une place pour le NULL */
	{
		argv[i++] = token;
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
