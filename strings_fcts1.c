#include "shell.h"

/**
 * _strlen - function that returns the length of a string
 * @s: pointer to string
 * Return: length of string
*/

int _strlen(char *s)
{
	int x = 0;

	if (!s)
		return (0);

	while (*s++)
		x++;
	return (x);
}

/**
 * _strcmp - compares two strings
 * @s1: the first string to compare
 * @s2: the second strang to compare
 * Return: 0 if strings are equal, -1 if s1 < s2, 1 if s1 > s2
*/

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - function that checks if a string starts with a substring
 * @haystack: the string to search
 * @needle: the substring to search for
 * Return: pointer to the first matching character, or NULL if not found
*/

char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - function that concatenates two strings
 * @dest: the destination
 * @src: the source
 * Return: pointer to destination
*/

char *_strcat(char *dest, char *src)
{
	char *res = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (res);
}
