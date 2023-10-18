#include "header_file.h"

/**
 * _shellexit - Exits the shell.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: Exits with a given exit status.
 *         (0) if info->argv[0] != "exit"
 */
int _shellexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = string_to_int(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Invalid number: ");
			show_error_msg(info->argv[1]);
			_write_char_to_stderr('\n');
			return (1);
		}
		info->err_num = string_to_int(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _changedir - Changes the current directory of the process.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: Always 0.
 */
int _changedir(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		string_puts("TODO: >>Failure message here<<\n");
	if (!info->argv[1])
	{
		dir = _environment_variable(info, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = _environment_variable(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (string_cmp(info->argv[1], "-") == 0)
	{
		if (!_environment_variable(info, "OLDPWD="))
		{
			string_puts(s);
			write_char('\n');
			return (1);
		}
		string_puts(_environment_variable(info, "OLDPWD=")), write_char('\n');
		chdir_ret =
			chdir((dir = _environment_variable(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "Can't change directory!");
		show_error_msg(info->argv[1]);
		_write_char_to_stderr('\n');
	}
	else
	{
		add_env_variable(info, "OLDPWD", _environment_variable(info, "PWD="));
		add_env_variable(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _seehelp - Provides help information (not yet implemented).
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: Always 0.
 */
int _seehelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	string_puts("Help function works\n");
	if (0)
		string_puts(*arg_array);
	return (0);
}
