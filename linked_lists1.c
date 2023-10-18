#include "header_file.h"

/**
 * count_nodes - Counts the number of nodes in a linked list.
 * @h: Pointer to the first node.
 *
 * Return: The total number of nodes in the list.
 */
size_t count_nodes(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return i;
}

/**
 * list_to_strings - Converts a linked list to an array of strings.
 * @head: Pointer to the first node.
 *
 * Return: An array of strings.
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = count_nodes(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return NULL;

	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return NULL;

	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(string_len(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return NULL;
		}

		str = string_cpy(str, node->str);
		strs[i] = str;
	}

	strs[i] = NULL;
	return strs;
}

/**
 * show_list - Prints all elements of a list_t linked list.
 * @h: Pointer to the first node.
 *
 * Return: The number of elements in the list.
 */
size_t show_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		string_puts(converts_number(h->num, 10, 0));
		write_char(':');
		write_char(' ');
		string_puts(h->str ? h->str : "(nil)");
		string_puts("\n");
		h = h->next;
		i++;
	}
	return i;
}

/**
 * find_node_with_prefix - Returns a node whose string starts with a given prefix.
 * @node: Pointer to list head.
 * @prefix: The prefix to match.
 * @c: The next character after the prefix to match (-1 if any character).
 *
 * Return: The matching node or NULL if not found.
 */
list_t *find_node_with_prefix(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = needle_starts(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return node;
		node = node->next;
	}
	return NULL;
}

/**
 * retrieve_node_index - Retrieves the index of a specific node in a linked list.
 * @head: Pointer to the list head.
 * @node: Pointer to the node.
 *
 * Return: The index of the node or -1 if the node is not found.
 */
ssize_t retrieve_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return i;
		head = head->next;
		i++;
	}
	return -1;
}
