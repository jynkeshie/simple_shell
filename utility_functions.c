#include "header_file.h"

/**
 * interactive_mode - Checks if the shell is in interactive_mode mode.
 * @info: The structure containing information about the shell.
 *
 * Return: 1 if the shell is in interactive_mode mode, 0 otherwise.
 */
int interactive_mode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * char_delim - Checks if a character is a delimiter.
 * @c: The character to check.
 * @delim: The delimiter string.
 *
 * Return: 1 if true, 0 if false.
 */
int char_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * char_alpha - Checks if a character is alphabetic.
 * @c: The character to check.
 *
 * Return: 1 if 'c' is alphabetic, 0 otherwise.
 */
int char_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * conv_str_int - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: 0 if there are no numbers in the string, the converted number otherwise.
 */
int conv_str_int(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
