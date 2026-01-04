#include "main.h"
#include <signal.h>
#include <unistd.h>

/**
* sigint_handler - handles Ctrl+C (SIGINT) and prints a new prompt
* @sig: signal number (ignored)
*/
void sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n($) ", 4);
}

/**
* main - entry point for the shell
* @argc: number of arguments (unused)
* @argv: array of arguments (argv[0] is the shell name)
*
* Return: 0 on success
*/
int main(int argc, char **argv)
{
	(void)argc;
	signal(SIGINT, sigint_handler);
	run_shell(argv[0]);
	return (0);
}
