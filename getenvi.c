#include "shell.h"

/**
 * get_environ - function that returns the environment
 * @info: Struct for potential arguments
 * Return: 0 on success
*/

char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - function to remove an environment variable
 * @info: Struct for potential arguments
 *  Return: 1 on success, 0 otherwise
 * @var: the string environment variable property
*/

int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t x = 0;
	char *ptr;

	if (!node || !var)
		return (0);

	while (node)
	{
		ptr = starts_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), x);
			x = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		x++;
	}
	return (info->env_changed);
}

/**
 * _setenv - function to set an environment variable
 *  or create one if it doesn't exist yet
 * @info: Struct for potential arguments
 * @var: the environment variable property
 * @value: the value of the environment variable
 *  Return: 0 on success
*/

int _setenv(info_t *info, char *var, char *value)
{
	char *bufferr = NULL;
	list_t *node;
	char *ptr;

	if (!var || !value)
		return (0);

	bufferr = malloc(_strlen(var) + _strlen(value) + 2);
	if (!bufferr)
		return (1);
	_strcpy(bufferr, var);
	_strcat(bufferr, "=");
	_strcat(bufferr, value);
	node = info->env;
	while (node)
	{
		ptr = starts_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = bufferr;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), bufferr, 0);
	free(bufferr);
	info->env_changed = 1;
	return (0);
}
