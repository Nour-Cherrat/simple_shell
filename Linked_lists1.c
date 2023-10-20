#include "shell.h"

/**
 * add_node - function that adds a node to the beginning of a list
 * @head: the address of the pointer to the first node
 * @str: the string to be added to the new node
 * @num: the index of the node
 * Return: the address of the new node, or NULL on failure
*/

list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *nv;

	if (!head)
		return (NULL);
	nv = malloc(sizeof(list_t));
	if (!nv)
		return (NULL);
	_memset((void *)nv, 0, sizeof(list_t));
	nv->num = num;
	if (str)
	{
		nv->str = _strdup(str);
		if (!nv->str)
		{
			free(nv);
			return (NULL);
		}
	}
	nv->next = *head;
	*head = nv;
	return (nv);
}

/**
 * add_node_end - function that adds a node to the end of a list
 * @head: the address of the pointer to the first node
 * @str: the string to be added to the new node
 * @num: the index of the node
 * Return: the address of the new node, or NULL on failure
*/

list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *nv, *node;

	if (!head)
		return (NULL);

	node = *head;
	nv = malloc(sizeof(list_t));
	if (!nv)
		return (NULL);
	_memset((void *)nv, 0, sizeof(list_t));
	nv->num = num;
	if (str)
	{
		nv->str = _strdup(str);
		if (!nv->str)
		{
			free(nv);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = nv;
	}
	else
		*head = nv;
	return (nv);
}

/**
 * print_list_str - function that prints all elements of a list_t linked
 * list
 * @h: pointer to first node
 * Return: number of nodes
*/

size_t print_list_str(const list_t *h)
{
	size_t x = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		x++;
	}
	return (x);
}

/**
 * delete_node_at_index - function that deletes a node at a given index
 * @head: pointer to pointer to first node
 * @index: index of node to delete
 * Return: 1 on success, -1 on failure
*/

int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *p_node;
	unsigned int x = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (x == index)
		{
			p_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		x++;
		p_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - function that frees a list_t list
 * @head_ptr: pointer to pointer to first node
 * Return: nothing
*/

void free_list(list_t **head_ptr)
{
	list_t *node, *n_node, *h;

	if (!head_ptr || !*head_ptr)
		return;
	h = *head_ptr;
	node = h;
	while (node)
	{
		n_node = node->next;
		free(node->str);
		free(node);
		node = n_node;
	}
	*head_ptr = NULL;
}
