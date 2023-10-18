#include "header_file.h"

/**
 * clear_info - Initializes fields of the info_t struct, setting them to NULL or 0.
 * @info: The address of the info_t struct to be cleared.
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * initialize_info - Initializes the info_t struct with provided values.
 * @info: The address of the info_t struct to be initialized.
 * @av: The argument vector (typically from the command line).
 */
void initialize_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = tokenize_string(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = string_dpl(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias_string(info);
		replace_vars_string(info);
	}
}

/**
 * free_info - Frees fields within the info_t struct, as necessary.
 * @info: The address of the info_t struct to be freed.
 * @all: True if all fields should be freed, false otherwise.
 */
void free_info(info_t *info, int all)
{
	free_string(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			clear_list(&(info->env));
		if (info->history)
			clear_list(&(info->history));
		if (info->alias)
			clear_list(&(info->alias));
		free_string(info->environ);
		info->environ = NULL;
		free_pointer((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		write_char(BUF_FLUSH);
	}
}
