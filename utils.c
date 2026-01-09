#include "main.h"

/**
* _strlen - Returns the length of a string
* @s: Input string
* Return: Length of s
*/
int _strlen(char *s)
{
	int len = 0;

	while (s[len])
		len++;
	return (len);
}

/**
* _strcpy - Copies a string
* @dest: Destination buffer
* @src: Source string
* Return: Pointer to dest
*/
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
* _strchr - Locates first occurrence of c in s
* @s: Input string
* @c: Character to find
* Return: Pointer to first occurrence of c, or NULL
*/
char *_strchr(char *s, char c)
{
	int i = 0;

	if (!s)
		return (NULL);

	while (s[i])
	{
		if (s[i] == c)
			return (s + i);
		i++;
	}

	if (c == '\0')
		return (s + i);

	return (NULL);
}
