#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

/**
 * get_cd_path - determines the path for the cd command
 * @args: array of command arguments
 * @oldpwd: previous working directory
 *
 * Return: path to change to, or NULL on failure
 *
 * This static function is used only in this file.
 * It handles:
 *   - "cd -" : returns the previous directory
 *   - "cd" with no argument : returns HOME
 *   - "cd <path>" : returns the given path
 */
static char *get_cd_path(char **args, char *oldpwd)
{
	char *path;

	if (args[1] && strcmp(args[1], "-") == 0)
	{
		if (!oldpwd)
		{
			write(STDERR_FILENO, "cd: OLDPWD not set\n", 19);
			return (NULL);
		}
		printf("%s\n", oldpwd);
		return (oldpwd);
	}

	if (args[1] == NULL)
	{
		path = getenv("HOME");
		if (!path)
		{
			write(STDERR_FILENO, "cd: HOME not set\n", 17);
			return (NULL);
		}
		return (path);
	}

	return (args[1]);
}

/**
 * handle_cd - changes the current working directory
 * @args: array of arguments for the cd command
 *
 * Return: 0 on success, 1 on failure
 *
 * This function automatically updates the previous working directory (OLDPWD)
 * and handles errors such as "HOME not set" or "OLDPWD not set".
 */
int handle_cd(char **args)
{
	static char *oldpwd;
	char cwd[1024];
	char *path;

	if (!getcwd(cwd, sizeof(cwd)))
		return (1);

	path = get_cd_path(args, oldpwd);
	if (!path)
		return (1);

	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}

	free(oldpwd);
	oldpwd = strdup(cwd);

	return (0);
}
