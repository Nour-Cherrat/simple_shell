#include "shell.h"

/**
 * _strcpy - Function that copies the string pointed to by src,
 * including the terminating null byte (\0), to the buffer pointed to by dest.
 * @dest: the destination Buffer
 * @src: the source Buffer
 * Return: the pointer to dest
*/

char *_strcpy(char *dest, char *src)
{
	int x = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[x])
	{
		dest[x] = src[x];
		x++;
	}
	dest[x] = 0;
	return (dest);
}

/**
 * _strdup - function that returns a pointer to a newly allocated space
 * @str: the string to be duplicated
 * Return: a pointer to the duplicated string, or NULL if insufficient memory
*/

char *_strdup(const char *str)
{
	int len = 0;
	char *res;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	for (len++; len--;)
		res[len] = *--str;
	return (res);
}

/**
 * _puts - function that prints a string
 * @str: the string
 * Return: void
*/

void _puts(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		_putchar(str[x]);
		x++;
	}
}

/**
 * _putchar - function that writes a character to stdout
 * @c: the character
 * Return: 1 on success, -1 on error
*/

int _putchar(char c)
{
	static int x;
	static char bufferr[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(1, bufferr, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		bufferr[x++] = c;
	return (1);
}
