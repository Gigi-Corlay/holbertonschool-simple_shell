#include "main.h"
#include <stdio.h>

/**
 * handle_env - prints the environment
 * @args: arguments array
 */
void handle_env(char **args)
{
	int i = 0;

	(void)args;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
