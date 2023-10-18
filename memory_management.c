#include "header_file.h"

/**
 * resize_memory_block - Reallocates a block of memory.
 * @ptr: Pointer to the previously allocated memory.
 * @old_size: Size of the currently allocated memory block.
 * @new_size: Size of the new memory block.
 *
 * This function reallocates a block of memory. If ptr is NULL, it behaves
 * like malloc and allocates a new block of memory of the specified new_size.
 * If new_size is 0, it behaves like free and releases the memory pointed to by ptr.
 *
 * Return: Pointer to the newly reallocated memory, or NULL on failure.
 */
void *resize_memory_block(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

/**
 * fill_memory - Fills a block of memory with a specified value.
 * @s: Pointer to the memory block to be filled.
 * @b: The value to fill the memory with.
 * @n: Number of bytes to fill.
 *
 * This function fills a block of memory pointed to by s with the value b for n bytes.
 *
 * Return: The pointer to the filled memory block.
 */
char *fill_memory(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * free_string - Frees a block of memory allocated for a string array.
 * @pp: Pointer to the string array to be freed.
 *
 * This function frees a block of memory allocated for an array of strings.
 */
void free_string(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}
