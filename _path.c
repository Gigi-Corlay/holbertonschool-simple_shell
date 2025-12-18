#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

extern char **environ;

char *_path(const char *command)
{
	char *path_value;
	char *path_copy;
	char *token;
	int len;
	char *full_path;

	path_value = getenv("PATH");
	if (!path_value)
		return NULL;

	path_copy = strdup(path_value);
	if (!path_copy)
		return NULL;
	
	token = strtok(path_copy, ":");
		while (token)
		{
		len = strlen(token) + strlen(command) + 2;

		full_path = malloc(len);
		if (!full_path)
		{
			free(path_copy);
			return NULL;
		}

		sprintf(full_path, "%s/%s", token, command);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return full_path;
		}

		free(full_path);
		token = strtok(NULL, ":");
		}

	free(path_copy);
	return NULL;
}

int main(void)
{
	char *cmd = "ls";
	char *res = _path(cmd);

	if (res)
	{
		printf("Full path: %s\n", res);
		free(res);
	}
	else
		printf("Command not found\n");

	return 0;
}
