#include "header_file.h"

/**
 * char_del - Test if current character in buffer is a chain delimeter.
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buffer
 *
 */
int char_del(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * monitor_chain.
 * @info: the parameter struct.
 * @buf: the char buffer.
 * @p: address of current position in buffer.
 * @i: starting position in buf.
 * @len: length of buffer.
 */
void monitor_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias_string.
 * @info: the parameter struct.
 *
 */
int replace_alias_string(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = find_node_with_prefix(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = string_char(node->str, '=');
		if (!p)
			return (0);
		p = string_dpl(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars_string.
 * @info: the parameter struct.
 *
 */
int replace_vars_string(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!string_cmp(info->argv[i], "$?"))
		{
			replace_data_string(&(info->argv[i]),
								string_dpl(converts_number(info->status, 10, 0)));
			continue;
		}
		if (!string_cmp(info->argv[i], "$$"))
		{
			replace_data_string(&(info->argv[i]),
								string_dpl(converts_number(getpid(), 10, 0)));
			continue;
		}
		node = find_node_with_prefix(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_data_string(&(info->argv[i]),
								string_dpl(string_char(node->str, '=') + 1));
			continue;
		}
		replace_data_string(&info->argv[i], string_dpl(""));
	}
	return (0);
}

/**
 * replace_data_string
 * @old: address of old string
 * @new: new string
 */
int replace_data_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
