#include "shell.h"

/**
 **_strncpy - function that copies a string
 *@dest: the destination
 *@src: the source
 *@n: the number of bytes to be copied
 *Return: (c) a pointer to the memory area c
*/

char *_strncpy(char *dest, char *src, int n)
{
	int x, y;
	char *c = dest;

	x = 0;
	while (src[x] != '\0' && x < n - 1)
	{
		dest[x] = src[x];
		x++;
	}
	if (x < n)
	{
		y = x;
		while (y < n)
		{
			dest[y] = '\0';
			y++;
		}
	}
	return (c);
}

/**
 **_strncat - function that concatenates two strings
 *@dest: the destination
 *@src: the source
 *@n: the number of bytes to be copied
 *Return: (c) a pointer to the memory area c
*/

char *_strncat(char *dest, char *src, int n)
{
	int x, y;
	char *c = dest;

	x = 0;
	y = 0;
	while (dest[x] != '\0')
		x++;
	while (src[y] != '\0' && y < n)
	{
		dest[x] = src[y];
		x++;
		y++;
	}
	if (y < n)
		dest[x] = '\0';
	return (c);
}

/**
 **_strchr - function that locates a character in a string
 *@s: the first string
 *@c: the second string
 *Return: (s) a pointer to the memory area s
*/

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
