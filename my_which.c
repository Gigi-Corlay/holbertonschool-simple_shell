#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

/**
 * get_path_from_env - Récupère la valeur de la variable PATH depuis envp
 * @envp: tableau des variables d'environnement
 *
 * Return: pointeur vers la valeur de PATH (ne pas free!), ou NULL si absente
 */
char *get_path_from_env(char **envp)
{
	int i, j;

	for (i = 0; envp[i] != NULL; i++)
	{
		for (j = 0; j < 5; j++)
		{
			if (envp[i][j] != "PATH="[j])
				break;
		}
		if (j == 5)
			return (envp[i] + 5);
	}
	return NULL;
}

/**
 * _strdup - copie une chaîne de caractères dans une nouvelle zone mémoire
 * @str: chaîne à copier
 *
 * Return: pointeur vers la nouvelle chaîne (malloc), ou NULL si échec
 */
char *_strdup(char *str)
{
	int len = 0, i;
	char *copy;

	if (!str)
		return NULL;

	while (str[len] != '\0')
		len++;

	copy = malloc(len + 1);
	if (!copy)
		return NULL;

	for (i = 0; i < len; i++)
		copy[i] = str[i];

	copy[len] = '\0';
	return copy;
}

/**
 * _which - Retourne le chemin complet d'une commande
 * @command: nom de la commande
 * @envp: tableau des variables d'environnement
 *
 * Return: chemin complet (à libérer) si trouvé, sinon NULL
 */
char *_which(char *command, char **envp)
{
	char *path, *path_copy, *token, *full_path;
	int len;

	/* Si command contient un '/', retourner une copie */
	for (int i = 0; command[i]; i++)
	{
		if (command[i] == '/')
			return _strdup(command);
	}

	/* Récupérer PATH depuis envp */
	path = get_path_from_env(envp);
	if (!path)
		return NULL;

	path_copy = _strdup(path);
	if (!path_copy)
		return NULL;

	token = strtok(path_copy, ":");
	while (token)
	{
		/* '/' + '\0' */
		len = strlen(token) + strlen(command) + 2; 
		full_path = malloc(len);
		if (!full_path)
		{
			free(path_copy);
			return NULL;
		}

		sprintf(full_path, "%s/%s", token, command);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return full_path;
		}

		free(full_path);
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return NULL;
}
