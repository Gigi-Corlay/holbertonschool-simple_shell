#include "main.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * find_path - Find full path of a command in PATH
 * @cmd: command name
 *
 * Return: malloc'ed full path string or NULL
 */
char *find_path(char *cmd)
{
	char *path_env, *path_copy, *token, *full_path;
	int len;

	if (!cmd)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (strdup(cmd));

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);

	path_copy = strdup(path_env);
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
		sprintf(full_path, "%s/%s", token, cmd);
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
