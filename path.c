#include "main.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

/**
* build_fullpath - Concatenates directory and command to a full path
* @dir: Directory path
* @cmd: Command name
* Return: Full path string (malloc'ed), or NULL on failure
*/
char *build_fullpath(char *dir, char *cmd)
{
	char *full;

	int i, j, len_dir, len_cmd;

	if (!dir || !cmd)
		return (NULL);

	len_dir = _strlen(dir);
	len_cmd = _strlen(cmd);

	/* +2 for '/' and '\0' */
	full = malloc(sizeof(char) * (len_dir + len_cmd + 2));
	if (!full)
		return (NULL);

	/* Copy directory */
	for (i = 0; dir[i]; i++)
		full[i] = dir[i];

	full[i++] = '/';

	/* Copy command */
	for (j = 0; cmd[j]; j++, i++)
		full[i] = cmd[j];

	full[i] = '\0';

	return (full);
}

/**
* handle_slash_cmd - Checks if command contains a '/' and is executable
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
* find_command_in_path - Searches for command in directories from PATH
* @cmd: Command string
* Return: Full path string if found (malloc'ed), NULL otherwise
*/
char *find_command_in_path(char *cmd)
{
	char *path_env, *path_copy, *dir, *full_path;

	if (!cmd || _strchr(cmd, '/'))
		return (handle_slash_cmd(cmd));

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);

	path_copy = malloc(sizeof(char) * (_strlen(path_env) + 1));
	if (!path_copy)
		return (NULL);

	_strcpy(path_copy, path_env);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		full_path = build_fullpath(dir, cmd);
		if (!full_path)
		{
			dir = strtok(NULL, ":");
			continue;
		}
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
