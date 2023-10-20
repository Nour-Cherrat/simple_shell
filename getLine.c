#include "shell.h"

/**
 * input_buf - function to read input buffer
 * @info: Strct for potential arguments
 * @buf: the buffer
 * @len: the length
 * Return: the number of bytes read
*/

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t res = 0;
	size_t lenth = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		res = getline(buf, &lenth, stdin);
#else
		res = _getline(info, buf, &lenth);
#endif
		if (res > 0)
		{
			if ((*buf)[res - 1] == '\n')
			{
				(*buf)[res - 1] = '\0';
				res--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';'))*/
			{
				*len = res;
				info->cmd_buf = buf;
			}
		}
	}
	return (res);
}

/**
 * get_input - function to get input from user
 * @info: Strct for potential arguments
 * Return: the number of bytes read
*/

ssize_t get_input(info_t *info)
{
	static char *bufferr;
	static size_t x, y, l;
	ssize_t res = 0;
	char **bufferr_p = &(info->arg), *ptr;

	_putchar(BUF_FLUSH);
	res = input_buf(info, &bufferr, &l);
	if (res == -1)
		return (-1);
	if (l)
	{
		y = x;
		ptr = bufferr + x;

		check_chain(info, bufferr, &y, x, l);
		while (y < l)
		{
			if (is_chain(info, bufferr, &y))
				break;
			y++;
		}

		x = y + 1;
		if (x >= l)
		{
			x = l = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*bufferr_p = ptr;
		return (_strlen(ptr));
	}

	*bufferr_p = bufferr;
	return (res);
}

/**
 * read_buf - function to read buffer
 * @info: struct for potential arguments
 * @buf: the buffer
 * @i: the size of the buffer
 * Return: result of read on success, 0 on EOF, -1 on error
*/

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t res = 0;

	if (*i)
		return (0);
	res = read(info->readfd, buf, READ_BUF_SIZE);
	if (res >= 0)
		*i = res;
	return (res);
}

/**
 * _getline - function to get line from file descriptor
 * @info: Struct for potential arguments
 * @ptr: pointer to buffer to store line
 * @length: pointer to length of buffer
 * Return: the number of bytes read
*/

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char bufferr[READ_BUF_SIZE];
	static size_t x, l;
	size_t y;
	ssize_t res = 0, st = 0;
	char *ptr1 = NULL, *nptr = NULL, *s;

	ptr1 = *ptr;
	if (ptr1 && length)
		st = *length;
	if (x == l)
		x = l = 0;

	res = read_buf(info, bufferr, &l);
	if (res == -1 || (res == 0 && l == 0))
		return (-1);

	s = _strchr(bufferr + x, '\n');
	y = s ? 1 + (unsigned int)(s - bufferr) : l;
	nptr = _realloc(ptr, st, st ? st + y : y + 1);
	if (!nptr) /* MALLOC FAILURE! */
		return (ptr1 ? free(ptr1), -1 : -1);

	if (st)
		_strncat(nptr, bufferr + x, y - x);
	else
		_strncpy(nptr, bufferr + x, y - x + 1);

	st += y - x;
	x = y;
	ptr1 = nptr;

	if (length)
		*length = st;
	*ptr = ptr1;
	return (st);
}

/**
 * sigintHandler - function to handle SIGINT
 * @sig_num: signal number
 * Return: nothing
*/

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
