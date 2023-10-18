#include "header_file.h"

/**
 * file_cmd - Determines if a file is an executable command.
 * @info: The info struct.
 * @path: Path to the file.
 *
 * Return: 1 if the file is an executable command, 0 otherwise.
 */
int file_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_chars - Duplicates characters from a
 * string within a specified range.
 * @pathstr: The input string.
 * @start: The starting index (inclusive).
 * @stop: The stopping index (exclusive).
 *
 * Return: A pointer to a new buffer containing the duplicated characters.
 */
char *duplicate_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
	{
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	}
	buf[k] = 0;
	return (buf);
}

/**
 * locate_path - Finds the full path of a command in the PATH environment variable.
 * @info: The info struct.
 * @pathstr: The PATH environment variable string.
 * @cmd: The command to find.
 *
 * Return: The full path of the command if found, or NULL if not found.
 */
char *locate_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((string_len(cmd) > 2) && needle_starts(cmd, "./"))
	{
		if (file_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = duplicate_chars(pathstr, curr_pos, i);
			if (!*path)
				string_conc(path, cmd);
			else
			{
				string_conc(path, "/");
				string_conc(path, cmd);
			}
			if (file_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
