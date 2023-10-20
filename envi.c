#include "shell.h"

/**
 * _myenv - function to print the environment
 * @info: Struct for potential arguments
 * Return: 0 on success
*/

int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv -function to get the environment variable
 * @info: Struct for potential arguments
 * @name: environment variable to get
 * Return: the value of the environment variable
*/

char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *ptr;

	while (node)
	{
		ptr = starts_with(node->str, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - function to set the environment variable
 * @info: Struct for potential arguments
 *  Return: 0 on success, 1 on failure
*/

int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - function to unset the environment variable
 * @info: Struct for potential arguments
 * Return: 0 on success
*/

int _myunsetenv(info_t *info)
{
	int x;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (x = 1; x <= info->argc; x++)
		_unsetenv(info, info->argv[x]);

	return (0);
}

/**
 * populate_env_list - function to populate the environment list
 * @info: Struct for potential arguments
 * Return: 0 on success
*/

int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t x;

	for (x = 0; environ[x]; x++)
		add_node_end(&node, environ[x], 0);
	info->env = node;
	return (0);
}
