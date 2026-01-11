#include "main.h"
#include <stdio.h>

/**
 * sigint_handler - Handle Ctrl+C
 * @sig: signal number (unused)
 */
void sigint_handler(int sig)
{
	(void)sig;
	putchar('\n');
	printf("$ ");
	fflush(stdout);
}
