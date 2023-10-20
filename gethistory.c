#include "shell.h"

/**
 * get_history_file - function to get history file
 * @info: Struct for potential arguments
 * Return: pointer to the new buffer
*/
char *get_history_file(info_t *info)
{
	char *bufferr, *direct;

	direct = _getenv(info, "HOME=");
	if (!direct)
		return (NULL);
	bufferr = malloc(sizeof(char) * (_strlen(direct) + _strlen(HIST_FILE) + 2));
	if (!bufferr)
		return (NULL);
	bufferr[0] = 0;
	_strcpy(bufferr, direct);
	_strcat(bufferr, "/");
	_strcat(bufferr, HIST_FILE);
	return (bufferr);
}

/**
 * write_history - function to write history to file
 * @info: struct for potential arguments
 * Return: 1 on success, -1 otherwise
*/

int write_history(info_t *info)
{
	ssize_t f;
	char *fname = get_history_file(info);
	list_t *node = NULL;

	if (!fname)
		return (-1);

	f = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (f == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, f);
		_putfd('\n', f);
	}
	_putfd(BUF_FLUSH, f);
	close(f);
	return (1);
}

/**
 * read_history - function to read history from file
 * @info: Struct for potential arguments
 * Return: result of renumber_history on success, 0 otherwise
*/

int read_history(info_t *info)
{
	int x, l = 0, count = 0;
	ssize_t f, len, size = 0;
	struct stat s;
	char *bufferr = NULL, *fname = get_history_file(info);

	if (!fname)
		return (0);

	f = open(fname, O_RDONLY);
	free(fname);
	if (f == -1)
		return (0);
	if (!fstat(f, &s))
		size = s.st_size;
	if (size < 2)
		return (0);
	bufferr = malloc(sizeof(char) * (size + 1));
	if (!bufferr)
		return (0);
	len = read(f, bufferr, size);
	bufferr[size] = 0;
	if (len <= 0)
		return (free(bufferr), 0);
	close(f);
	for (x = 0; x < size; x++)
		if (bufferr[x] == '\n')
		{
			bufferr[x] = 0;
			build_history_list(info, bufferr + l, count++);
			l = x + 1;
		}
	if (l != x)
		build_history_list(info, bufferr + l, count++);
	free(bufferr);
	info->histcount = count;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - function to build history linked list
 * @info: Struct for potential arguments
 * @buf: the buffer
 * @linecount: the history lines counter
 * Return: 0 on success
*/

int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - function to renumber history
 * @info: Struct for potential arguments
 * Return: the new histcount value on success, -1 otherwise
*/

int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int x = 0;

	while (node)
	{
		node->num = x++;
		node = node->next;
	}
	return (info->histcount = x);
}
