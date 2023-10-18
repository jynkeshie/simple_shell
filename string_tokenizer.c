#include "header_file.h"

/**
 * tokenize_string - Splits a string into words using a custom delimiter.
 * @str: The input string to be split.
 * @delimiter: The delimiter string.
 *
 * Return: An array of strings, or NULL on failure.
 */
char **tokenize_string(char *str, char *delimiter)
{
	int i, j, k, m, numwords = 0;
	char **words;

	if (str == NULL || str[0] == 0)
		return NULL;

	if (!delimiter)
		delimiter = " ";

	for (i = 0; str[i] != '\0'; i++)
	{
		if (!char_delim(str[i], delimiter) && (char_delim(str[i + 1], delimiter) || !str[i + 1]))
			numwords++;
	}

	if (numwords == 0)
		return NULL;

	words = malloc((1 + numwords) * sizeof(char *));
	if (!words)
		return NULL;

	for (i = 0, j = 0; j < numwords; j++)
	{
		while (char_delim(str[i], delimiter))
			i++;

		k = 0;
		while (!char_delim(str[i + k], delimiter) && str[i + k])
			k++;

		words[j] = malloc((k + 1) * sizeof(char));
		if (!words[j])
		{
			for (k = 0; k < j; k++)
				free(words[k]);
			free(words);
			return NULL;
		}

		for (m = 0; m < k; m++)
			words[j][m] = str[i++];

		words[j][m] = 0;
	}

	words[j] = NULL;
	return words;
}

/**
 * split_string - Splits a string into words using a specified delimiter character.
 * @str: The input string to be split.
 * @delimiter: The delimiter character.
 *
 * Return: An array of strings, or NULL on failure.
 */
char **split_string(char *str, char delimiter)
{
	int i, j, k, m, numwords = 0;
	char **words;

	if (str == NULL || str[0] == 0)
		return NULL;

	for (i = 0; str[i] != '\0'; i++)
	{
		if ((str[i] != delimiter && str[i + 1] == delimiter) ||
			(str[i] != delimiter && !str[i + 1]) || str[i + 1] == delimiter)
			numwords++;
	}

	if (numwords == 0)
		return NULL;

	words = malloc((1 + numwords) * sizeof(char *));
	if (!words)
		return NULL;

	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == delimiter && str[i] != delimiter)
			i++;

		k = 0;
		while (str[i + k] != delimiter && str[i + k] && str[i + k] != delimiter)
			k++;

		words[j] = malloc((k + 1) * sizeof(char));
		if (!words[j])
		{
			for (k = 0; k < j; k++)
				free(words[k]);
			free(words);
			return NULL;
		}

		for (m = 0; m < k; m++)
			words[j][m] = str[i++];

		words[j][m] = 0;
	}

	words[j] = NULL;
	return words;
}
