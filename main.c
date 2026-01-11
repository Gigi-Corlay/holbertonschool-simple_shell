#include "main.h"

/**
* main - Entry point of shell
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
