#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;
/*
* env et environ → même tableau
* copy (si tu en fais une copie) → nouveau tableau, donc adresses différentes
* %p + (void *) → bonne manière de vérifier les adresses en C
*/
int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	int n = 0, i;
	char **copy;

	/* compter le nombre de variables d'environnement */
	while (env[n] != NULL)
		n++;

	/* allouer de la mémoire pour le tableau de pointeurs*/
	copy = malloc((n + 1) * sizeof(char *));
	if (!copy)
	{
		perror("malloc");
		return (1);
	}

	/* allouer chaque chaîne */
	for (i = 0; i < n; i++)
	{
		/* strdup fait malloc + copy */
		copy[i] = strdup(env[i]);
		if (!copy[i])
		{
			perror("strdup");
			/*libérer ce qui a été alloué jusqu'ici*/
			for (int j = 0; j < i; j++)
				/* Libérer chaque chaîne */
				free(copy[j]);
			/* Libérer le tableau de pointeurs */
			free(copy);
			return (1);
		}
	}
	copy[n] = NULL;

	/*Affichage des adresses env et environ*/
	printf("%p\n", (void *)env);
	printf("%p\n", (void *)environ);

	/* libérer la mémoire */
	for (i = 0; i < n; i++)
		free(copy[i]);
	free(copy);

	return (0);
}
/**
* env (le troisième paramètre de main) et 
* environ (la variable globale) pointent 
* vers le même tableau d’environnement 
* fourni par le système.
*/
