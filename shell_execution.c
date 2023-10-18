#include "header_file.h"

/**
 * hsh - Main shell loop.
 * @info: The parameter & return info struct.
 * @av: The argument vector from main().
 *
 * Return: 0 on success, 1 on error, or error code.
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive_mode(info))
			string_puts("shell$ ");
		_write_char_to_stderr(BUF_FLUSH);
		r = get_line_input(info);
		if (r != -1)
		{
			initialize_info(info, av);
			builtin_ret = builtin_command(info);
			if (builtin_ret == -1)
				command_path(info);
		}
		else if (interactive_mode(info))
			write_char('\n');
		free_info(info, 0);
	}
	save_history_to_file(info);
	free_info(info, 1);
	if (!interactive_mode(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * builtin_command - Finds a built-in command.
 * @info: The parameter & return info struct.
 *
 * Return: The return code from the built-in command.
 */
int builtin_command(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _shellexit},
		{"env", _listenv},
		{"help", _seehelp},
		{"history", _allhistory},
		{"setenv", _setenvironment},
		{"unsetenv", _unsetenvironment},
		{"cd", _changedir},
		{"alias", _myalias},
		{NULL, NULL}};

	for (i = 0; builtintbl[i].type; i++)
		if (string_cmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * command_path - Finds a command in the PATH.
 * @info: The parameter & return info struct.
 */
void command_path(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!char_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = locate_path(info, _environment_variable(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_command(info);
	}
	else
	{
		if ((interactive_mode(info) || _environment_variable(info, "PATH=") || info->argv[0][0] == '/') && file_cmd(info, info->argv[0]))
			fork_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "Not Available\n");
		}
	}
}

/**
 * fork_command - Forks a child process to execute a command.
 * @info: The parameter & return info struct.
 */
void fork_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, copy_env_strings(info)) == -1)
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
