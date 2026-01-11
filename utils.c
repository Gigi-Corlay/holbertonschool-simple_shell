#include "main.h"

/**
* _strlen - Returns the length of a string
* @s: Input string
* Return: Length of the string
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
* _strcpy - Copies a string from src to dest
* @dest: Destination buffer
* @src: Source string
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
* _atoi - Converts a string to integer
* @s: Input string
* Return: Converted integer value
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
* _strchr - Locates first occurrence of character in string
* @s: Input string
* @c: Character to locate
* Return: Pointer to first occurrence or NULL if not found
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
