#include "main.h"
#include <signal.h>

/**
 * sigint_handler - handles Ctrl+C
 * @sig: signal number
 */
void sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n($) ", 4);
}

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 * Return: 0
 */
int main(int argc, char **argv)
{
	(void)argc;

	signal(SIGINT, sigint_handler);
	run_shell(argv[0]);

	return (0);
}
