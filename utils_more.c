#include "main.h"

/**
* _atoi - Converts string to integer
* @s: Input string
* Return: Converted integer
*/
int _atoi(char *s)
{
	int i = 0, sign = 1, res = 0;

	if (!s)
		return (0);
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + (s[i] - '0');
		i++;
	}
	return (res * sign);
}

/**
* _getenv - Gets value of an environment variable
* @name: Variable name
* Return: Pointer to value or NULL
*/
char *_getenv(const char *name)
{
	int i, j, len;

	if (!name || !environ)
		return (NULL);

	len = 0;
	while (name[len])
		len++;

	for (i = 0; environ[i]; i++)
	{
		j = 0;
		while (environ[i][j] && name[j] &&
			environ[i][j] == name[j])
			j++;
		if (name[j] == '\0' && environ[i][j] == '=')
			return (environ[i] + j + 1);
	}
	return (NULL);
}
