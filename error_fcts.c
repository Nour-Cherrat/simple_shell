#include "shell.h"

/**
 * _erratoi - function that converts a string to an integer
 * @s: the string
 * Return: Result on success, -1 on error
*/

int _erratoi(char *s)
{
	int x = 0;
	unsigned long int res = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (x = 0;  s[x] != '\0'; x++)
	{
		if (s[x] >= '0' && s[x] <= '9')
		{
			res *= 10;
			res += (s[x] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_error - function that prints error messages
 * @info: Struct for potential arguments
 * @estr: string that contains the error type
 * Return: void
*/

void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - prints a decimal number to stdout
 * @input: the input number
 * @fd: the filedescriptor
 * Return: the number of characters printed
*/

int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int x, N = 0;
	unsigned int ab, curr;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		ab = -input;
		__putchar('-');
		N++;
	}
	else
		ab = input;
	curr = ab;
	for (x = 1000000000; x > 1; x /= 10)
	{
		if (ab / x)
		{
			__putchar('0' + curr / x);
			N++;
		}
		curr %= x;
	}
	__putchar('0' + curr);
	N++;

	return (N);
}

/**
 * convert_number - function that converts a number to a string
 * @num: the number
 * @base: the base to convert to
 * @flags: the argument flags
 * Return: the string representation of the number
*/

char *convert_number(long int num, int base, int flags)
{
	static char *a;
	static char buff[50];
	char s = 0;
	char *p;
	unsigned long N = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		N = -num;
		s = '-';

	}
	a = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buff[49];
	*p = '\0';

	do	{
		*--p = a[N % base];
		N /= base;
	} while (N != 0);

	if (s)
		*--p = s;
	return (p);
}

/**
 * remove_comments - replaces the first '#' character with a null byte
 * @buf: the address of the string
 * Return: 0 on success
*/

void remove_comments(char *buf)
{
	int x;

	for (x = 0; buf[x] != '\0'; x++)
		if (buf[x] == '#' && (!x || buf[x - 1] == ' '))
		{
			buf[x] = '\0';
			break;
		}
}
