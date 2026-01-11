#include "main.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
* _getenv - Gets the value of an environment variable
* @name: Variable name
* Return: Pointer to value or NULL if not found
*/
char *_getenv(const char *name)
{
	int i, j, len;

	if (!name || !environ)
		return (NULL);

	len = 0;
	while (name[len])
		len++;

	for (i = 0; environ[i]; i++)
	{
		j = 0;
		while (environ[i][j] && name[j] && environ[i][j] == name[j])
			j++;
		if (name[j] == '\0' && environ[i][j] == '=')
			return (environ[i] + j + 1);
	}
	return (NULL);
}

/**
* build_fullpath - Concatenates directory and command
* @dir: Directory path
* @cmd: Command name
* Return: Full path string (malloc'ed) or NULL
*/
char *build_fullpath(char *dir, char *cmd)
{
	int i, j;

	char *full;

	if (!dir || !cmd)
		return (NULL);
	full = malloc(_strlen(dir) + _strlen(cmd) + 2);
	if (!full)
		return (NULL);
	for (i = 0; dir[i]; i++)
		full[i] = dir[i];
	full[i++] = '/';
	for (j = 0; cmd[j]; j++, i++)
		full[i] = cmd[j];
	full[i] = '\0';
	return (full);
}

/**
* handle_slash_cmd - Checks if a command with '/' is executable
* @cmd: Command string
* Return: Command string if executable, NULL otherwise
*/
char *handle_slash_cmd(char *cmd)
{
	if (!cmd)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (cmd);
	return (NULL);
}

/**
* find_command_in_path - Searches command in PATH environment variable
* @cmd: Command string
* Return: Full path (malloc'ed) or NULL
*/
char *find_command_in_path(char *cmd)
{
	char *path_env, *path_copy, *dir, *full;

	if (!cmd || _strchr(cmd, '/'))
		return (handle_slash_cmd(cmd));

	path_env = _getenv("PATH");
	if (!path_env)
		return (NULL);

	path_copy = malloc(_strlen(path_env) + 1);
	if (!path_copy)
		return (NULL);

	_strcpy(path_copy, path_env);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		full = build_fullpath(dir, cmd);
		if (full && access(full, X_OK) == 0)
		{
			free(path_copy);
			return (full);
		}
		free(full);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
