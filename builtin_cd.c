#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

/**
 * get_env_value - get value of an environment variable from environ
 * @name: variable name (e.g. "HOME")
 *
 * Return: pointer to value or NULL if not found
 */
char *get_env_value(const char *name)
{
	int i = 0;
	size_t len;

	if (!name)
		return (NULL);

	len = strlen(name);

	while (environ[i])
	{
		if (strncmp(environ[i], name, len) == 0 &&
		    environ[i][len] == '=')
			return (environ[i] + len + 1);
		i++;
	}
	return (NULL);
}

/**
 * get_cd_path - determines the path for the cd command
 * @args: array of command arguments
 * @oldpwd: previous working directory
 *
 * Return: path to change to, or NULL on failure
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
		path = get_env_value("HOME");
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
 */
int handle_cd(char **args)
{
	static char *oldpwd;
	char cwd[1024];
	char *path;
	char *new_oldpwd;

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

	new_oldpwd = malloc(strlen(cwd) + 1);
	if (!new_oldpwd)
		return (1);

	strcpy(new_oldpwd, cwd);
	free(oldpwd);
	oldpwd = new_oldpwd;

	return (0);
}
