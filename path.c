#include "main.h"
#include <stdlib.h>
#include <unistd.h>

/**
* _getenv - Gets the value of an environment variable
* @name: Name of the environment variable
*
* Return: Pointer to the value, or NULL if not found
*/
char *_getenv(const char *name)
{
	int i = 0, j;

	while (environ[i])
	{
		j = 0;
		while (name[j] && environ[i][j] == name[j])
			j++;

		if (name[j] == '\0' && environ[i][j] == '=')
			return (environ[i] + j + 1);
		i++;
	}
	return (NULL);
}

/**
* handle_slash_cmd - Handles commands containing a '/'
* @cmd: Command to check
*
* Return: Malloc'ed path if executable, or NULL on failure
*/
char *handle_slash_cmd(char *cmd)
{
	char *copy;

	int len;

	if (!cmd)
		return (NULL);

	if (access(cmd, X_OK) != 0)
		return (NULL);

	len = _strlen(cmd);
	copy = malloc(len + 1);
	if (!copy)
		return (NULL);

	_strcpy(copy, cmd);
	return (copy);
}

/**
* build_fullpath - Builds a full path from directory and command
* @dir: Directory from PATH
* @cmd: Command name
*
* Return: Malloc'ed full path, or NULL on failure
*/
char *build_fullpath(char *dir, char *cmd)
{
	char *full;

	int i = 0, j = 0;

	full = malloc(_strlen(dir) + _strlen(cmd) + 2);
	if (!full)
		return (NULL);

	while (dir[i])
	{
		full[i] = dir[i];
		i++;
	}
	full[i++] = '/';

	while (cmd[j])
		full[i++] = cmd[j++];

	full[i] = '\0';
	return (full);
}

/**
* find_command_in_path - Finds a command in PATH directories
* @cmd: Command to search
*
* Return: Malloc'ed full path if found, or NULL otherwise
*/
char *find_command_in_path(char *cmd)
{
	char *path, *path_copy, *dir, *full;

	if (!cmd)
		return (NULL);

	if (_strchr(cmd, '/'))
		return (handle_slash_cmd(cmd));

	path = _getenv("PATH");
	if (!path || path[0] == '\0')
		return (NULL);

	path_copy = malloc(_strlen(path) + 1);
	if (!path_copy)
		return (NULL);
	_strcpy(path_copy, path);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		if (dir[0] == '\0')  /* chemin vide :: ou début/fin PATH */
			dir = ".";

		full = build_fullpath(dir, cmd);
		if (!full)
			break;

		if (access(full, X_OK) == 0)
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
