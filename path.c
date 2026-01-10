#include "main.h"
#include <string.h>

/**
 * find_path - Find command in PATH
 * @cmd: Command name
 * Return: Full path or NULL
 */
char *find_path(char *cmd)
{
	char *path, *dir, *full;
	struct stat st;

	if (stat(cmd, &st) == 0)
		return (cmd);

	path = getenv("PATH");
	if (!path)
		return (NULL);

	dir = strtok(path, ":");
	while (dir)
	{
		full = malloc(_strlen(dir) + _strlen(cmd) + 2);
		if (!full)
			return (NULL);

		sprintf(full, "%s/%s", dir, cmd);
		if (stat(full, &st) == 0)
			return (full);

		free(full);
		dir = strtok(NULL, ":");
	}
	return (NULL);
}
