#include "main.h"

/**
 * myexit - exits the shell
 * @info: struct
 *
 * Return: exits with given exit
 */

int myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = _errtoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_err(info, "illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _errtoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}
/**
 * mycd - changes the current dir
 * @info: struct
 *
 * Return: 0 Always.
 */
int mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		perror("getcwd");;
	if (!info->argv[1])
	{
		dir = get_env(info, "HOME=");
		if (!dir)
		{
			chdir_ret = chdir((dir = get_env(info, "PWD=")) ? dir : "/");
			chdir((dir = get_env(info, "PWD=")) ? dir : "/");
		}
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!get_env(info, "OLDPWD="))
		{
			_puts(s);
			putchar('\n');
			return (1);
		}
		_puts(get_env(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dir = get_env(info, "OLDPWD=")) ? dir : "/");
			chdir((dir = get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_err(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		setenv("PWD", getcwd(buffer, 1024), 1);
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
