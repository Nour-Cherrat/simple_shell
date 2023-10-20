#include "shell.h"

/**
 * _myexit - function to exit the shell
 * @info: The structure that contains potential arguments
 * Return: exits with an exit status of 0
 * or 1 on failure or -2 on exit call
*/

int _myexit(info_t *info)
{
	int checker;

	if (info->argv[1]) /* if there is an argument */
	{
		checker = _erratoi(info->argv[1]);
		if (checker == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - function to change the current directory of the process
 * @info: Structure containing potential arguments
 * Return: 0 on success
*/

int _mycd(info_t *info)
{
	char *str, *direct, buff[1024];
	int chdirect_ret;

	str = getcwd(buff, 1024);
	if (!str)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		direct = _getenv(info, "HOME=");
		if (!direct)
			chdirect_ret =
				chdir((direct = _getenv(info, "PWD=")) ? direct : "/");
		else
			chdirect_ret = chdir(direct);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdirect_ret =
			chdir((direct = _getenv(info, "OLDPWD=")) ? direct : "/");
	}
	else
		chdirect_ret = chdir(info->argv[1]);
	if (chdirect_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * _myhelp - function that changes the current directory of the process
 * @info: Structure containing potential arguments
 * Return: 0 on success
*/

int _myhelp(info_t *info)
{
	char **args_array;

	args_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*args_array); /* to get rid of unused variable warning */
	return (0);
}
