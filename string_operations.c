#include "header_file.h"

/**
 * copy_string - Copies the first 'n' characters from the source string to the destination string.
 * @dest: The destination string to copy to.
 * @src: The source string.
 * @n: The maximum number of characters to copy.
 *
 * Returns: A pointer to the modified destination string.
 */
char *copy_string(char *dest, char *src, int n)
{
	int i;
	char *result = dest;

	for (i = 0; i < n - 1 && src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';

	return result;
}

/**
 * string_cat - Concatenates the first 'n' bytes of the source string.
 * @dest: The destination string.
 * @src: The source string.
 * @n: The maximum number of bytes to concatenate.
 *
 * Returns: A pointer to the modified destination string.
 */
char *string_cat(char *dest, char *src, int n)
{
	int dest_len = string_len(dest);
	int i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';

	return dest;
}

/**
 * string_char - Searches for the first occurrence of a character 'c' in the input string 's'.
 * @s: The string to search within.
 * @c: The character to look for.
 *
 * Returns: A pointer to the first occurrence of 'c' in 's', or NULL if not found.
 */
char *string_char(char *s, char c)
{
	do
	{
		if (*s == c)
			return s;
	} while (*s++ != '\0');

	return NULL;
}
