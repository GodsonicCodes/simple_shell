#include "shell.h"




/**
 * _myhistory - Displays the history list, one command per line, preceded
 * by line numbers, starting at 0.
 *
 * @info: Structure containing potential arguments, used to maintain a
 * constant function prototype.
 *
 * Return: Always returns 0.
 */


/*Function _myhistory*/
int _myhistory(info_t *info)
{
    print_list(info->history); /* Print the history list. */
    return (0);
}



/**
 * unset_alias - Unsets (deletes) an alias with the given string.
 *
 * @info: Parameter structure containing information.
 * @str: The string representing the alias to be unset.
 *
 * Return: Always returns 0 on success, 1 on error.
 */


/*function unset_alias*/
int unset_alias(info_t *info, char *str)
{
    char *p, c;
    int ret;

    p = _strchr(str, '='); /* Find the position of the equal sign '=' in the string. */
    if (!p)
        return (1); /* Return 1 to indicate an error if the equal sign is not found. */
    c = *p;
    *p = 0; /* Replace the equal sign with a null character to separate the alias name. */
    ret = delete_node_at_index(&(info->alias),
                              get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
    *p = c; /* Restore the original character. */
    return (ret);
}




/**
 * set_alias - Sets an alias to the given string.
 *
 * @info: Parameter structure containing information.
 * @str: The string representing the alias to be set.
 *
 * Return: Always returns 0 on success, 1 on error.
 */



/*set_alias*/
int set_alias(info_t *info, char *str)
{
    char *p;

    p = _strchr(str, '='); /* Find the position of the equal sign '=' in the string. */
    if (!p)
        return (1); /* Return 1 to indicate an error if the equal sign is not found. */
    if (!*++p)
        return (unset_alias(info, str)); /* Unset the alias if there is no content after the equal sign. */
    unset_alias(info, str); /* Unset the alias with the same name to update it. */
    return (add_node_end(&(info->alias), str, 0) == NULL); /* Add the updated alias to the alias list. */
}




/**
 * print_alias - Prints an alias string.
 *
 * @node: The alias node to be printed.
 *
 * Return: Always returns 0 on success, 1 on error.
 */



/*function print_alias*/
int print_alias(list_t *node)
{
    char *p = NULL, *a = NULL;

    if (node)
    {
        p = _strchr(node->str, '='); /* Find the position of the equal sign '=' in the alias string. */
        for (a = node->str; a <= p; a++)
            _putchar(*a); /* Print each character of the alias name. */
        _putchar('\''); /* Print a single quote to enclose the alias value. */
        _puts(p + 1); /* Print the alias value. */
        _puts("'\n"); /* Print a newline character to separate aliases. */
        return (0);
    }
    return (1); /* Return 1 to indicate an error if the alias node is not found. */
}




/**
 * _myalias - Mimics the alias builtin (as described in the man page for alias).
 *
 * @info: Parameter structure containing information.
 *
 * Return: Always returns 0.
 */



/*function _myalias*/
int _myalias(info_t *info)
{
    int i = 0;
    char *p = NULL;
    list_t *node = NULL;

    if (info->argc == 1) /* Check if there are no arguments (only 'alias' is entered). */
    {
        node = info->alias;
        while (node)
        {
            print_alias(node); /* Print each alias. */
            node = node->next;
        }
        return (0);
    }
    for (i = 1; info->argv[i]; i++)
    {
        p = _strchr(info->argv[i], '='); /* Find the position of the equal sign '=' in the argument. */
        if (p)
            set_alias(info, info->argv[i]); /* Set the alias if the equal sign is found. */
        else
            print_alias(node_starts_with(info->alias, info->argv[i], '=')); /* Print the alias if it exists. */
    }

    return (0);
}
