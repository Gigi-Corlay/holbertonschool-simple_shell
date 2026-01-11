#include <signal.h>
#include "main.h"

/**
* main - Entry point for the shell
* @argc: number of arguments
* @argv: argument array
* Return: Always 0
*/
int main(int argc, char **argv)
{
	(void)argc;

	signal(SIGINT, sigint_handler);
	run_shell(argv[0]);

	return (0);
}
