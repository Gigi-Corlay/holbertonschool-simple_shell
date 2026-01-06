#include "main.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * read_line - lit une ligne depuis stdin
 * @len: pointeur sur la taille du buffer (getline met à jour)
 * Return: pointeur vers la ligne (à free), NULL si EOF
 */
char *read_line(size_t *len)
{
	if (handle_exit(args))
	{
		free(args);
		free(line);
		exit(0);
	}

	if (nread > 0 && line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	return (line);
}

/**
 * handle_env - implémentation du builtin env
 * @args: tableau d'arguments
 */
void handle_env(char **args)
{
	int i = 0;

	(void)args;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

/**
 * handle_exit - check si la commande est exit et quitte le shell
 * @args: tableau d'arguments
 * @line: ligne originale
 * Return: 1 si exit a été appelé, 0 sinon
 */
int handle_exit(char **args, char *line)
{
	if (strcmp(args[0], "exit") == 0)
	{
		free(args);
		free(line);
		return;
	}

	execute(argv0, args, *line_number);
	free(args);
	free(line);
}

/**
 * handle_stdin - boucle principale du shell
 * @argv0: nom du shell (pour les messages d'erreur)
 * @line_number: pointeur sur le compteur de lignes
 */
void handle_stdin(char *argv0, int *line_number)
{
	int interactive = isatty(STDIN_FILENO);
	size_t len = 0;
	char *line;
	char **args;

	while (1)
	{
		if (interactive)
			print_prompt();

		line = read_line(&len);
		if (!line)
			break;

		(*line_number)++;

		if (line[0] == '\0')
		{
			free(line);
			continue;
		}

		args = parse_args(line);
		if (!args || !args[0])
		{
			free(args);
			free(line);
			continue;
		}

		process_line(argv0, args, line, line_number);
	}

	if (interactive)
		write(STDOUT_FILENO, "\n", 1);
	exit(0);
}

/**
 * run_shell - point d'entrée du shell
 * @argv0: nom du shell (pour messages d'erreur)
 */
void run_shell(char *argv0)
{
	int line_number = 0;

	handle_stdin(argv0, &line_number);
}
