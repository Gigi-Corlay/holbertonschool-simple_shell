#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

char *_getenv(const char *name)
{
	int len_name, len_in_env;
	char *ptr;

	len_name = strlen(name);

	for (int i = 0; environ[i] != NULL; i++)
	{
		ptr = strchr(environ[i], '=');
		len_in_env = ptr - environ[i];

		if (len_name == len_in_env && strncmp(environ[i], name, len_name) == 0)
			return (ptr + 1);
	}

	return (NULL);
}

int main(void)
{
	char *path = _getenv("PATH");

	if (path != NULL)
		printf("PATH = %s\n", path);
	else
		printf("Variable not found\n");

	return (0);
}
