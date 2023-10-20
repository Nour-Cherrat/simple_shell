#include "shell.h"

/**
 * _eputs - function that prints a string to stderr
 * @str: the string
 * Return: void
*/

void _eputs(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		_eputchar(str[x]);
		x++;
	}
}

/**
 * _eputchar - function that prints a character to stderr
 * @c: The character
 * Return: 1 on success, -1 on error
*/

int _eputchar(char c)
{
	static int x;
	static char bufferr[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(2, bufferr, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		bufferr[x++] = c;
	return (1);
}

/**
 * _putfd - function that prints a character to a filedescriptor
 * @c: The character
 * @fd: The filedescriptor
 * Return: 1 on success, -1 on error
*/

int _putfd(char c, int fd)
{
	static int x;
	static char bufferr[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(fd, bufferr, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		bufferr[x++] = c;
	return (1);
}

/**
 * _putsfd - function that prints a string to a filedescriptor
 * @str: the string
 * @fd: the filedescriptor
 * Return: the number of characters printed
*/

int _putsfd(char *str, int fd)
{
	int x = 0;

	if (!str)
		return (0);
	while (*str)
	{
		x += _putfd(*str++, fd);
	}
	return (x);
}
