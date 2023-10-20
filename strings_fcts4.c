#include "shell.h"

/**
 * **strtow - function that splits a string into words
 * @str: the input
 * @d: the delimeter
 * Return: the pointer to the array of strings, NULL on failure
*/

char **strtow(char *str, char *d)
{
	int x, y, z, w, nwords = 0;
	char **ch;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (x = 0; str[x] != '\0'; x++)
		if (!is_delim(str[x], d) && (is_delim(str[x + 1], d) || !str[x + 1]))
			nwords++;

	if (nwords == 0)
		return (NULL);
	ch = malloc((1 + nwords) * sizeof(char *));
	if (!ch)
		return (NULL);
	for (x = 0, y = 0; y < nwords; y++)
	{
		while (is_delim(str[x], d))
			x++;
		z = 0;
		while (!is_delim(str[x + z], d) && str[x + z])
			z++;
		ch[y] = malloc((z + 1) * sizeof(char));
		if (!ch[y])
		{
			for (z = 0; z < y; z++)
				free(ch[z]);
			free(ch);
			return (NULL);
		}
		for (w = 0; w < z; w++)
			ch[y][w] = str[x++];
		ch[y][w] = 0;
	}
	ch[y] = NULL;
	return (ch);
}

/**
 * **strtow2 - function that splits a string into words
 * @str: the input
 * @d: the delimeter
 * Return: the pointer to the array of strings, NULL on failure
*/

char **strtow2(char *str, char d)
{
	int x, y, z, w, nwords = 0;
	char **ch;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (x = 0; str[x] != '\0'; x++)
		if ((str[x] != d && str[x + 1] == d) ||
				    (str[x] != d && !str[x + 1]) || str[x + 1] == d)
			nwords++;
	if (nwords == 0)
		return (NULL);
	ch = malloc((1 + nwords) * sizeof(char *));
	if (!ch)
		return (NULL);
	for (x = 0, y = 0; y < nwords; y++)
	{
		while (str[x] == d && str[x] != d)
			x++;
		z = 0;
		while (str[x + z] != d && str[x + z] && str[x + z] != d)
			z++;
		ch[y] = malloc((z + 1) * sizeof(char));
		if (!ch[y])
		{
			for (z = 0; z < y; z++)
				free(ch[z]);
			free(ch);
			return (NULL);
		}
		for (w = 0; w < z; w++)
			ch[y][w] = str[x++];
		ch[y][w] = 0;
	}
	ch[y] = NULL;
	return (ch);
}
