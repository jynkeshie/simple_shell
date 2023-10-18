#include "header_file.h"

/**
 * _allhistory - Displays the history list, one command per line, preceded
 * with line numbers starting at 0.
 * @info: Parameter struct for maintaining function prototype.
 *
 * Return: Always 0.
 */
int _allhistory(info_t *info)
{
	list_t *node = info->history;
	show_list(node);
	return (0);
}

/**
 * remove_alias - Unsets an alias by its name.
 * @info: Parameter struct.
 * @str: The alias string to unset.
 *
 * Return: Always 0 on success, 1 on error.
 */
int remove_alias(info_t *info, char *str)
{
	char *p;
	char c;
	int ret;

	p = string_char(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = remove_node_at_index(&(info->alias),
							   retrieve_node_index(info->alias, find_node_with_prefix(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * add_alias - Sets an alias to a string.
 * @info: Parameter struct.
 * @str: The alias string to set.
 *
 * Return: Always 0 on success, 1 on error.
 */
int add_alias(info_t *info, char *str)
{
	char *p;

	p = string_char(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (remove_alias(info, str));

	remove_alias(info, str);
	return (append_node(&(info->alias), str, 0) == NULL);
}

/**
 * display_alias - Prints an alias string.
 * @node: The alias node.
 *
 * Return: Always 0 on success, 1 on error.
 */
int display_alias(list_t *node)
{
	char *p = NULL;
	char *a = NULL;

	if (node)
	{
		p = string_char(node->str, '=');
		for (a = node->str; a <= p; a++)
			write_char(*a);
		write_char('\'');
		string_puts(p + 1);
		string_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Mimics the alias built-in (man alias).
 * @info: Parameter struct for maintaining function prototype.
 *
 * Return: Always 0.
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			display_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = string_char(info->argv[i], '=');
		if (p)
			add_alias(info, info->argv[i]);
		else
			display_alias(find_node_with_prefix(info->alias, info->argv[i], '='));
	}

	return (0);
}
