#include "shell.h"

/**
 * hsh - the main shell function
 * @info: Struct for potential parameters
 * @av: the argument vector
 * Return: 0 if successful, 1 if not
*/

int hsh(info_t *info, char **av)
{
	ssize_t res = 0;
	int built_ret = 0;

	while (res != -1 && built_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		res = get_input(info);
		if (res != -1)
		{
			set_info(info, av);
			built_ret = find_builtin(info);
			if (built_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (built_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (built_ret);
}

/**
 * find_builtin - function that finds a builtin
 * @info: Struct for potential arguments
 * Return: 0 if successful, 1 if not
*/

int find_builtin(info_t *info)
{
	int x, built_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (x = 0; builtintbl[x].type; x++)
		if (_strcmp(info->argv[0], builtintbl[x].type) == 0)
		{
			info->line_count++;
			built_ret = builtintbl[x].func(info);
			break;
		}
	return (built_ret);
}

/**
 * find_cmd - function that finds a command in the path
 * @info: Struct for potential arguments
 * Return: nothing
*/

void find_cmd(info_t *info)
{
	char *p = NULL;
	int x, y;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (x = 0, y = 0; info->arg[x]; x++)
		if (!is_delim(info->arg[x], " \t\n"))
			y++;
	if (!y)
		return;

	p = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (p)
	{
		info->path = p;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - function that forks a command
 * @info: Struct for potential arguments
 * Return: nothing
*/

void fork_cmd(info_t *info)
{
	pid_t ch_pid;

	ch_pid = fork();
	if (ch_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (ch_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
