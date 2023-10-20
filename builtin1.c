#include "shell.h"

/**
 * _myexit - Function for shell exit
 * @info: Structure containing potential arguments
 * Return: Exits with exit status 0 on success, 1 on failure, or -2 on exit call
 */

int _myexit(info_t *info)
{
	int exit_code;

	if (info->argv[1])
	{
		exit_code = _erratoi(info->argv[1]);
		if (exit_code == -1)
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
 * _mycd - Function to change the current directory of the process
 * @info: Structure holding potential arguments
 * Return: 0 on success
 */

int _mycd(info_t *info)
{
    char *current_dir, *new_dir, buffer[1024];
    int change_dir_ret;

    current_dir = getcwd(buffer, 1024);
    if (!current_dir)
        _puts("TODO: >>getcwd failure emsg here<<\n");
    if (!info->argv[1])
    {
        new_dir = _getenv(info, "HOME=");
        if (!new_dir)
            change_dir_ret = chdir((new_dir = _getenv(info, "PWD=")) ? new_dir : "/");
        else
            change_dir_ret = chdir(new_dir);
    }
    else if (_strcmp(info->argv[1], "-") == 0)
    {
        if (!_getenv(info, "OLDPWD="))
        {
            _puts(current_dir);
            _putchar('\n');
            return (1);
        }
        _puts(_getenv(info, "OLDPWD="));
        _putchar('\n');
        change_dir_ret = chdir((new_dir = _getenv(info, "OLDPWD=")) ? new_dir : "/");
    }
    else
        change_dir_ret = chdir(info->argv[1]);
    if (change_dir_ret == -1)
    {
        print_error(info, "can't cd to ");
        _eputs(info->argv[1]);
        _eputchar('\n');
    }
    else
    {
        _setenv(info, "OLDPWD", _getenv(info, "PWD="));
        _setenv(info, "PWD", getcwd(buffer, 1024));
    }
    return (0);
}


/**
 * _myhelp - Function to provide assistance and information
 * @info: Structure holding potential arguments
 * Return: 0 on success
 */


int _myhelp(info_t *info)
{
    char **arguments;

    arguments = info->argv;
    _puts("help call works. Function not yet implemented\n");
    if (0)
        _puts(*arguments);
    return (0);
}

