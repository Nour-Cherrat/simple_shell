#include "shell.h"

/**
 * _myhistory - function to print the history of commands entered by user
 * @info: Struct for potential arguments
 *  Return: 0 on success
*/

int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - unsets alias to string
 * @info: Struct for potential arguments
 * @str: the string
 * Return: 0 on success, 1 on error
*/

int unset_alias(info_t *info, char *str)
{
	char *ptr, s;
	int res;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	s = *ptr;
	*ptr = 0;
	res = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*ptr = s;
	return (res);
}

/**
 * set_alias -function to set alias to string
 * @info: Struct for potential arguments
 * @str: the alias
 * Return: 0 on success, 1 on error
*/

int set_alias(info_t *info, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - function to print alias
 * @node: the alias node
 * Return: 0 on success, 1 on failure
*/

int print_alias(list_t *node)
{
	char *ptr = NULL, *alias = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');
		for (alias = node->str; alias <= ptr; alias++)
		_putchar(*alias);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - function to mimic alias
 * @info: Struct for potential arguments
 *  Return: 0 on success
*/

int _myalias(info_t *info)
{
	int x = 0;
	char *ptr = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (x = 1; info->argv[x]; x++)
	{
		ptr = _strchr(info->argv[x], '=');
		if (ptr)
			set_alias(info, info->argv[x]);
		else
			print_alias(node_starts_with(info->alias, info->argv[x], '='));
	}

	return (0);
}
