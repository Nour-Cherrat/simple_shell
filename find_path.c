#include "shell.h"

/**
 * is_cmd - function to check if a file is a cmd
 * @info: Stuct for potential arguments
 * @path: the path to the file
 * Return: 1 on success, 0 otherwise
*/

int is_cmd(info_t *info, char *path)
{
	struct stat s;

	(void)info;
	if (!path || stat(path, &s))
		return (0);

	if (s.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - function to duplicate chars from a string
 * @pathstr: the PATH
 * @start: the starting index
 * @stop: the stopping index
 * Return: pointer to the new buffer
*/

char *dup_chars(char *pathstr, int start, int stop)
{
	static char bufferr[1024];
	int x = 0, y = 0;

	for (y = 0, x = start; x < stop; x++)
		if (pathstr[x] != ':')
			bufferr[y++] = pathstr[x];
	bufferr[y] = 0;
	return (bufferr);
}

/**
 * find_path - function to find the full path of a cmd
 * @info: Struct for potential arguments
 * @pathstr: the PATH
 * @cmd: the cmd
 * Return: full path of cmd if found, NULL if not found
*/

char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int x = 0, curr = 0;
	char *p;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[x] || pathstr[x] == ':')
		{
			p = dup_chars(pathstr, curr, x);
			if (!*p)
				_strcat(p, cmd);
			else
			{
				_strcat(p, "/");
				_strcat(p, cmd);
			}
			if (is_cmd(info, p))
				return (p);
			if (!pathstr[x])
				break;
			curr = x;
		}
		x++;
	}
	return (NULL);
}
