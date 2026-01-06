#include "main.h"
#include <signal.h>
#include <unistd.h>

/**
* sigint_handler - handle Ctrl+C (SIGINT)
* @sig: signal number
*/
void sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
}

/**
* main - entry point of the shell
* @argc: argument count
* @argv: argument vector
* Return: 0 on success
*/
int main(int argc, char **argv)
{
	(void)argc;
	signal(SIGINT, sigint_handler);
	run_shell(argv[0]);
	return (0);
}
