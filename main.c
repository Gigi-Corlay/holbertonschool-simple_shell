#include "main.h"
#include <signal.h>
#include <unistd.h>

/**
* sigint_handler - handle Ctrl+C
* @sig: signal number
*/
void sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n($) ", 5);
}

/**
* main - entry point
* @argc: unused
* @argv: program name
*
* Return: 0
*/
int main(int argc, char **argv)
{
	(void)argc;
	signal(SIGINT, sigint_handler);
	run_shell(argv[0]);
	return (0);
}
