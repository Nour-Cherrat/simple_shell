#include "shell.h"

/**
 * bfree - function that frees a pointer and sets it to NULL
 * @ptr: the pointer to be freed
 * Return: 1 on success, 0 on failure
*/

int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
