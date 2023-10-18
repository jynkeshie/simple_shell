#include "header_file.h"

/**
 * main - The entry point for the simple shell.
 * @ac: The number of command-line arguments.
 * @av: An array of strings containing the command-line arguments.
 *
 * Return: 0 on success, 1 on error.
 */
int main(int ac, char **av)
{
	info_t info[] = {INFO_INIT}; /* Initialize an info_t struct */
	int fd = 2;

	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r"(fd)
		: "r"(fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				show_error_msg(av[0]);
				show_error_msg(": 0: Cannot open ");
				show_error_msg(av[1]);
				_write_char_to_stderr('\n');
				_write_char_to_stderr(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	initialize_env(info);
	load_history_from_file(info);
	hsh(info, av);
	return (EXIT_SUCCESS); /* Return 0 on successful execution */
}
