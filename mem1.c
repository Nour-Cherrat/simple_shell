#include "shell.h"

/**
 * _memset - function that fills memory with a constant byte
 * @s: memory area to be filled
 * @b: the constant byte
 * @n: the number of bytes to fill
 * Return: a pointer to the memory area s
*/

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int x;

	for (x = 0; x < n; x++)
		s[x] = b;
	return (s);
}

/**
 * ffree - function that frees a string of strings
 * @pp: the pointer to the string of strings
*/

void ffree(char **pp)
{
	char **ptr = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(ptr);
}

/**
 * _realloc - function that reallocates a memory block
 * using malloc and free
 * @ptr: pointer to the memory previously allocated
 * @old_size: byte size of allocated space for ptr
 * @new_size: byte size of new memory block
 * Return: pointer to the new memory block
*/

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *ptr1;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	ptr1 = malloc(new_size);
	if (!ptr1)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		ptr1[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (ptr1);
}
