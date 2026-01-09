#include "main.h"

/**
* builtin_env - Prints the environment variables
* @argv0: Shell name
*/
int builtin_env(char *argv0)
{
	int i;
	(void)argv0;

	for (i = 0; environ[i]; i++)
		printf("%s\n", environ[i]);

	return (1);
}
