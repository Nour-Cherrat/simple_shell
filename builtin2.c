#include "shell.h"

/**
 * _myhistory - Function to display the command history entered by the user
 * @info: Structure holding potential arguments
 * Return: 0 on success
 */


int _myhistory(info_t *info)
{
    print_list(info->command_history);
    return (0);
}


/**
 * unset_alias - Function to remove an alias by its string name
 * @info: Structure containing potential arguments
 * @str: The alias string to unset
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
 * set_alias - Function to set an alias to a string
 * @info: Structure holding potential arguments
 * @alias_str: The alias to set
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
 * print_alias - Function to display an alias
 * @node: The alias node to print
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
 * _myalias - Function to manage aliases
 * @info: Structure holding potential arguments
 * Return: 0 on success
 */


int _myalias(info_t *info)
{
	int index = 0;
	char *equal_sign_ptr = NULL;
	list_t *current_node = NULL;

	if (info->argc == 1)
	{
		current_node = info->alias;
		while (current_node)
		{
			print_alias(current_node);
			current_node = current_node->next;
		}
		return (0);
	}
	for (index = 1; info->argv[index]; index++)
	{
		equal_sign_ptr = _strchr(info->argv[index], '=');
		if (equal_sign_ptr)
			set_alias(info, info->argv[index]);
		else
			print_alias(node_starts_with(info->alias, info->argv[index], '='));
	}

	return (0);
}

