#include "main.h"
#include <signal.h>

/**
 * main - Entry point for the shell
 *
 * Return: 0 on success
 */
int main(void)
{
	signal(SIGINT, sigint_handler); /* handle Ctrl+C */
	shell_loop();                   /* start shell loop */
	return (0);                     /* exit shell process safely */
}
