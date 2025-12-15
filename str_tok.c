#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100

/**
* my_strtok - découpe une chaîne en mots
* @str: chaîne à découper (sera modifiée par strtok)
*
* Return: tableau de chaînes terminé par NULL, ou NULL en cas d'erreur
*/
char **my_strtok(char *str)
{
	char **argv;
	char *arg;
	char *token;
	int i = 0;
	int len, j;

	/* Allocation du tableau de pointeurs */
	argv = malloc(sizeof(char *) * MAX_WORDS);
	if (!argv)
		return (NULL);

	/* Premier token */
	token = strtok(str, " ");

	while (token != NULL)
	{
		/* Calcul manuel de la longueur */
		len = 0;
		while (token[len] != '\0')
			len++;

		/* Allocation pour un argument */
		arg = malloc(len + 1);
		if (!arg)
			return (NULL);

		/* Copie caractère par caractère */
        for (j = 0; j < len; j++)
            arg[j] = token[j];
        arg[len] = '\0';

        /* Stockage dans le tableau */
        argv[i] = arg;
		i++;

		/* Token suivant */
		token = strtok(NULL, " ");
	}

    /* Fin du tableau */
    argv[i] = NULL;

	return (argv);
}
