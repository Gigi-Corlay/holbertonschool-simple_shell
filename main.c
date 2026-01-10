#include "main.h"
#include <signal.h>

/**
* main - Entry point of the shell
* @argc: Argument count
* @argv: Argument vector
* Return: 0 on success
*/
int main(int argc, char **argv)
{
	(void)argc;

	signal(SIGINT, sigint_handler);
	run_shell(argv[0]);

	return (0);
}
