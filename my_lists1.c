#include "shell.h"




/* 
 * list_len - Determines the length of a linked list.
 *
 * @h: Pointer to the first node.
 *
 * Return: The size of the list.
 */





/*function list_len*/
size_t list_len(const list_t *h)
{
    size_t i = 0; /* Initialize a variable to count the number of nodes. */

    while (h) /* Loop through the linked list until the end is reached. */
    {
        h = h->next; /* Move to the next node. */
        i++; /* Increment the counter. */
    }
    return i; /* Return the total count. */
}




/* 
 * list_to_strings - Converts a linked list to an array of strings.
 *
 * @head: Pointer to the first node.
 *
 * Return: An array of strings.
 */





/*function list_to_strings*/
char **list_to_strings(list_t *head)
{
    list_t *node = head; /* Create a temporary pointer to traverse the list. */
    size_t i = list_len(head), j; /* Get the length of the list and declare an index. */
    char **strs; /* Declare an array of strings. */
    char *str;

    if (!head || !i) /* Check if the list is empty or has no nodes. */
        return NULL;

    strs = malloc(sizeof(char *) * (i + 1)); /* Allocate memory for the array of strings. */
    if (!strs) /* Check if memory allocation failed. */
        return NULL;

    for (i = 0; node; node = node->next, i++) /* Loop through the list to copy strings. */
    {
        str = malloc(_strlen(node->str) + 1); /* Allocate memory for each string. */
        if (!str) /* Check if memory allocation failed. */
        {
            for (j = 0; j < i; j++) /* Free previously allocated strings. */
                free(strs[j]);
            free(strs); /* Free the array of strings. */
            return NULL; /* Return NULL if memory allocation fails. */
        }

        str = _strcpy(str, node->str); /* Copy the string to the allocated memory. */
        strs[i] = str; /* Store the string in the array. */
    }
    strs[i] = NULL; /* Add a NULL pointer to the end of the array. */
    return strs; /* Return the array of strings. */
}





/* 
 * print_list - Prints all elements of a list_t linked list.
 *
 * @h: Pointer to the first node.
 *
 * Return: The size of the list.
 */





/*function print_list*/
size_t print_list(const list_t *h)
{
    size_t i = 0; /* Initialize a variable to count the number of nodes. */

    while (h) /* Loop through the linked list until the end is reached. */
    {
        _puts(convert_number(h->num, 10, 0)); /* Print the numerical value. */
        _putchar(':'); /* Print a colon. */
        _putchar(' '); /* Print a space. */
        _puts(h->str ? h->str : "(nil)"); /* Print the string or "(nil)" if it's NULL. */
        _puts("\n"); /* Print a newline character. */
        h = h->next; /* Move to the next node. */
        i++; /* Increment the counter. */
    }
    return i; /* Return the total count. */
}





/* 
 * node_starts_with - Returns the node whose string starts with a given prefix.
 *
 * @node: Pointer to the list head.
 * @prefix: String to match at the beginning.
 * @c: The next character after the prefix to match.
 *
 * Return: The matching node or NULL if not found.
 */





/*function node_starts_with*/
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
    char *p = NULL; /* Initialize a pointer to a character. */

    while (node) /* Loop through the linked list. */
    {
        p = starts_with(node->str, prefix); /* Check if the string starts with the prefix. */
        if (p && ((c == -1) || (*p == c))) /* Check if there's a match. */
            return node; /* Return the matching node. */
        node = node->next; /* Move to the next node. */
    }
    return NULL; /* Return NULL if no match is found. */
}





/* 
 * get_node_index - Gets the index of a node in a linked list.
 *
 * @head: Pointer to the list head.
 * @node: Pointer to the node to find the index of.
 *
 * Return: The index of the node or -1 if not found.
 */




/*function get_node_index*/
ssize_t get_node_index(list_t *head, list_t *node)
{
    size_t i = 0; /* Initialize a variable to count the number of nodes. */

    while (head) /* Loop through the linked list until the end is reached. */
    {
        if (head == node) /* Check if the current node matches the target node. */
            return i; /* Return the index of the node. */
        head = head->next; /* Move to the next node. */
        i++; /* Increment the counter. */
    }
    return -1; /* Return -1 if the node is not found in the list. */
}
