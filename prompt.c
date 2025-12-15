#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * main - simple shell prompt
 *
 * Description:
 *   Affiche un prompt "$ " et attend que l'utilisateur saisisse une commande.
 *   Lit la ligne saisie avec getline.
 *   Affiche la ligne entrée sur la ligne suivante.
 *   La lecture continue jusqu'à EOF (Ctrl+D) ou une erreur.
 *   Libère la mémoire allouée pour la ligne à la fin.
 *
 * Return: 0 (success)
 */
int main(void)
{
	/* Pointeur pour stocker la ligne lue*/
	char *line = NULL;

	/* taille du buffer */
	size_t len = 0;
	/* nombre de caractères lus */
	ssize_t nread;

	/* Affiche le prompt */
	printf("$ ");
	/* boucle conditionnée par getline */
	while ((nread = getline(&line, &len, stdin)) != -1)
	{
		/* Affiche la ligne */
		printf("%s", line);
		/* prompt pour la prochaine commande */
		printf("$ ");
	}
	/* libérer la mémoire allouée par getline */
	free(line);
	return (0);
}
