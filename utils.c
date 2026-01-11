#include "main.h"

/**
* _strlen - Returns length of string
* @s: Input string
* Return: Length
*/
int _strlen(char *s)
{
	int len = 0;

	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

/**
* _strcpy - Copies string from src to dest
* @dest: Destination
* @src: Source
* Return: Pointer to dest
*/
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (!dest || !src)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
* _strcmp - Compares two strings
* @s1: First string
* @s2: Second string
* Return: 0 if equal, <0 if s1<s2, >0 if s1>s2
*/
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

/**
* _strchr - Locates first occurrence of c in s
* @s: Input string
* @c: Character to find
* Return: Pointer to first occurrence or NULL
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
