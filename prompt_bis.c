#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
/**
* Affiche $ comme prompt
* Lit une ligne depuis l’utilisateur avec getline
* Affiche la ligne sur la ligne suivante
* Gère EOF / Ctrl+D pour sortir
* Libère la mémoire à la fin
*/
int main(void)
{
	/* Pointeur pour stocker la ligne lue*/
	char *line = NULL;

	/* taille du buffer */
	size_t len = 0;
	/* nombre de caractères lus */
	ssize_t nread;
	/* boucle infinie pour attendre les commandes. */
	while (1)
	{
	/* Affiche le prompt */
	printf("$ ");
	/* Force l'affichage */
	fflush(stdout);
	/**
	* LIRE LA LIGNE
	 * &line → getline peut allouer/réallouer le buffer
	 * &len → taille actuelle du buffer
	 * stdin → lire depuis l’entrée standard
	*/
	nread = getline(&line, &len, stdin);
	/* EOF ou erreur */
	if (nread == -1)
	/*sortir de la boucle quand EOF (Ctrl+D).*/
		break;
	/* Affiche la ligne */
	printf("%s", line);
	}
	/* libérer la mémoire allouée par getline */
	free(line);
	return (0);
}
