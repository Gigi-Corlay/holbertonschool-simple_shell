#include "main.h"

/**
 * main - entry point
 * @argc: number of arguments (unused)
 * @argv: array of arguments
 * Return: 0
 */
int main(int argc, char **argv)
{
	(void)argc;
	run_shell(argv[0]);
	return (0);
}
