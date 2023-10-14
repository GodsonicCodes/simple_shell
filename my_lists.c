#include "shell.h"




/**
 * add_node - Adds a node to the start of the list.
 * @head: Address of pointer to head node.
 * @str: str field of the node.
 * @num: Node index used by history.
 *
 * Return: Size of the list.
 */



/*function add_node*/
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	/* Check if the head is NULL */
	if (!head)
		return (NULL);

	/* Allocate memory for a new node */
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);

	/* Initialize the new node to zero */
	_memset((void *)new_head, 0, sizeof(list_t));

	/* Set the node index to the provided 'num' value */
	new_head->num = num;

	/* Duplicate the 'str' field if it is provided */
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}

	/* Update the new node's 'next' to point to the current head */
	new_head->next = *head;

	/* Update the head to point to the new node */
	*head = new_head;

	return (new_head);
}




/**
 * add_node_end - Adds a node to the end of the list.
 * @head: Address of pointer to head node.
 * @str: str field of the node.
 * @num: Node index used by history.
 *
 * Return: Size of the list.
 */



/*function add_node_end*/
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	/* Check if the head is NULL */
	if (!head)
		return (NULL);

	/* Point 'node' to the current head */
	node = *head;

	/* Allocate memory for a new node */
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	/* Initialize the new node to zero */
	_memset((void *)new_node, 0, sizeof(list_t));

	/* Set the node index to the provided 'num' value */
	new_node->num = num;

	/* Duplicate the 'str' field if it is provided */
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	/* Find the last node in the list */
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}





/**
 * print_list_str - Prints only the 'str' element of a list_t linked list.
 * @h: Pointer to the first node.
 *
 * Return: Size of the list.
 */



/*function print_list_str*/
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	/* Loop through the list and print the 'str' field or "(nil)" if NULL */
	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}





/**
 * delete_node_at_index - Deletes a node at the given index.
 * @head: Address of pointer to the first node.
 * @index: Index of the node to delete.
 *
 * Return: 1 on success, 0 on failure.
 */



/*function delete_node_at_index*/
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	/* Check if the head is NULL or if the list is empty */
	if (!head || !*head)
		return (0);

	/* Special case: Delete the first node */
	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}

	/* Loop through the list to find the node to delete */
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}





/**
 * free_list - Frees all nodes of a list.
 * @head_ptr: Address of pointer to the head node.
 *
 * Return: void
 */




/*function free_list*/
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	/* Check if the head pointer is NULL or if the list is empty */
	if (!head_ptr || !*head_ptr)
		return;

	/* Point 'head' to the head node */
	head = *head_ptr;
	node = head;

	/* Loop through the list, freeing each node and its 'str' field */
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}

	/* Set the head pointer to NULL to indicate an empty list */
	*head_ptr = NULL;
}

