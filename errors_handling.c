#include "header_file.h"

/**
 * string_to_int - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: The converted number if successful, or -1 on error.
 */
int string_to_int(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return -1;
		}
		else
			return -1;
	}
	return result;
}

/**
 * print_error - Prints an error message to the standard error.
 * @info: The parameter and return info struct.
 * @estr: String containing a specified error type.
 */
void print_error(info_t *info, char *estr)
{
	show_error_msg(info->fname);
	show_error_msg(": ");
	print_dec(info->line_count, STDERR_FILENO);
	show_error_msg(": ");
	show_error_msg(info->argv[0]);
	show_error_msg(": ");
	show_error_msg(estr);
}

/**
 * print_dec - Prints a decimal (integer) number (base 10) to the specified file descriptor.
 * @input: The input number to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */
int print_dec(int input, int fd)
{
	int (*__putchar)(char) = write_char;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _write_char_to_stderr;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return count;
}

/**
 * converts_number - Converter function for converting
 * 		a number to a string.
 * @num: The number to be converted.
 * @base: The base for the conversion.
 * @flags: Argument flags.
 *
 * Return: The resulting string.
 */
char *converts_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456abcd" : "0123456ABCD";
	ptr = &buffer[49];
	*ptr = '\0';

	do
	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return ptr;
}

/**
 * erase_comments - Replaces the first instance of
 * 		'#' with '\0' in the input string.
 * @buf: Address of the string to modify.
 */
void erase_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
