#include "header_file.h"

/**
 * see_file_history - Get the path to the history file.
 * @info: Parameter struct.
 *
 * Return: Allocated string containing the history file path.
 */
char *see_file_history(info_t *info)
{
	char *buf, *dir;

	dir = _environment_variable(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (string_len(dir) + string_len(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	string_cpy(buf, dir);
	string_conc(buf, "/");
	string_conc(buf, HIST_FILE);
	return (buf);
}

/**
 * save_history_to_file - Save the history list to a file.
 * @info: Parameter struct.
 *
 * Return: 1 on success, else -1.
 */
int save_history_to_file(info_t *info)
{
	ssize_t fd;
	char *filename = see_file_history(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_write_string_to_fd(node->str, fd);
		_write_to_fd('\n', fd);
	}
	_write_to_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * load_history_from_file - Load history from a file.
 * @info: Parameter struct.
 *
 * Return: histcount on success, 0 otherwise.
 */
int load_history_from_file(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = see_file_history(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			add_history_entry(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		add_history_entry(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		remove_node_at_index(&(info->history), 0);
	update_history_line_numbers(info);
	return (info->histcount);
}

/**
 * add_history_entry - Add a history entry to the linked list.
 * @info: Parameter struct.
 * @buf: Buffer containing the history entry.
 * @linecount: The history line count (histcount).
 *
 * Return: Always 0.
 */
int add_history_entry(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	append_node(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * update_history_line_numbers - Renumber the history linked
 * list after changes.
 * @info: Parameter struct.
 *
 * Return: The new histcount.
 */
int update_history_line_numbers(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
