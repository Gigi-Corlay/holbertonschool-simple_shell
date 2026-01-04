#include "main.h"

/**
* main - Entry point for the shell
* @argc: number of arguments (unused)
* @argv: array of arguments
* Return: 0 on success
*/
int main(int argc, char **argv)
{
	(void)argc;
	run_shell(argv[0]);
	return (0);
}
