#include "shell.h"

/**
 * list_len - function that returns the number of elements in a linked list_t
 * @h: pointer to first node
 * Return: number of elements
*/

size_t list_len(const list_t *h)
{
	size_t x = 0;

	while (h)
	{
		h = h->next;
		x++;
	}
	return (x);
}

/**
 * list_to_strings - function that converts a linked list to
 * an array of strings
 * @head: pointer to first node
 * Return: the array of strings
*/

char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t x = list_len(head), y;
	char **str;
	char *s;

	if (!head || !x)
		return (NULL);
	str = malloc(sizeof(char *) * (x + 1));
	if (!str)
		return (NULL);
	for (x = 0; node; node = node->next, x++)
	{
		s = malloc(_strlen(node->str) + 1);
		if (!s)
		{
			for (y = 0; y < x; y++)
				free(str[y]);
			free(str);
			return (NULL);
		}

		s = _strcpy(s, node->str);
		str[x] = s;
	}
	str[x] = NULL;
	return (str);
}


/**
 * print_list - function that prints all the elements of a list_t list
 * @h: pointer to first node
 * Return: the number of nodes
*/

size_t print_list(const list_t *h)
{
	size_t x = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		x++;
	}
	return (x);
}

/**
 * node_starts_with - function that finds a node that starts with a string
 * @node: pointer to first node
 * @prefix: the prefix to match
 * @c: the character to match
 * Return: pointer to node or NULL
*/

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = starts_with(node->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - function that returns the index of a node in a list
 * @head: pointer to first node
 * @node: pointer to node
 * Return: the index of the node or -1 if not found
*/

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t x = 0;

	while (head)
	{
		if (head == node)
			return (x);
		head = head->next;
		x++;
	}
	return (-1);
}
