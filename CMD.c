#include "shell.h"

/**
 * _newexit - exits the shell
 * @line: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if line.argv[0] != "exit"
 */
int _newexit(line_t *line)
{
	int exitcheck;

	if (line->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = _erratoi(line->argv[1]);
		if (exitcheck == -1)
		{
			line->status = 2;
			write_error(line, "Illegal number: ");
			_eputs(line->argv[1]);
			_eputchar('\n');
			return (1);
		}
		line->err_num = _erratoi(line->argv[1]);
		return (-2);
	}
	line->err_num = -1;
	return (-2);
}

/**
 * _newcd - changes the current directory of the process
 * @line: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _newcd(line_t *line)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!line->argv[1])
	{
		dir = _getenv(line, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(line, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(line->argv[1], "-") == 0)
	{
		if (!_getenv(line, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(line, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(line, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(line->argv[1]);
	if (chdir_ret == -1)
	{
		write_error(line, "can't cd to ");
		_eputs(line->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(line, "OLDPWD", _getenv(line, "PWD="));
		_setenv(line, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _newhelp - changes the current directory of the process
 * @line: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _newhelp(line_t *line)
{
	char **arg_array;

	arg_array = line->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
