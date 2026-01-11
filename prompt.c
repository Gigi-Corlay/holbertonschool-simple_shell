#include "main.h"
#include <unistd.h>

/**
* print_prompt - Prints shell prompt
*/
void print_prompt(void)
{
	write(STDOUT_FILENO, "($) ", 4);
}

/**
* sigint_handler - Handles Ctrl+C
* @sig: Signal number
*/
void sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n($) ", 5);
}
