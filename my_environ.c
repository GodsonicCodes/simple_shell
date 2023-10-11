#include "shell.h"



/**
 * _myenv - Display the current environment.
 *
 * @info: Structure containing potential arguments. Used to maintain
 *        a consistent function prototype.
 *
 * Return: Always 0.
 */


/*function _myenv*/
int _myenv(info_t *info)
{
    print_list_str(info->env); /* Print the list of environment variables. */
    return (0);
}



/**
 * _getenv - Retrieve the value of an environment variable.
 *
 * @info: Structure containing potential arguments. Used to maintain
 *        a consistent function prototype.
 * @name: The name of the environment variable.
 *
 * Return: The value of the environment variable, or NULL if not found.
 */


/*function _getenv*/
char *_getenv(info_t *info, const char *name)
{
    list_t *node = info->env;
    char *p;

    while (node)
    {
        p = starts_with(node->str, name); /* Check if the node's string starts with the specified name. */
        if (p && *p) /* If the name is found and not empty. */
            return (p); /* Return the value of the environment variable. */
        node = node->next;
    }
    return (NULL); /* Return NULL if the environment variable is not found. */
}




/**
 * _mysetenv - Create a new environment variable or modify an existing one.
 *
 * @info: Structure containing potential arguments. Used to maintain
 *        a consistent function prototype.
 *
 * Return: Always 0.
 */


/*function _mysetenv*/
int _mysetenv(info_t *info)
{
    if (info->argc != 3)
    {
        _eputs("Incorrect number of arguments\n"); /* Print an error message for an incorrect number of arguments. */
        return (1);
    }
    if (_setenv(info, info->argv[1], info->argv[2])) /* Set the environment variable using the specified name and value. */
        return (0);
    return (1);
}




/**
 * _myunsetenv - Remove an environment variable.
 *
 * @info: Structure containing potential arguments. Used to maintain
 *        a consistent function prototype.
 *
 * Return: Always 0.
 */


/*function _myunsetenv*/
int _myunsetenv(info_t *info)
{
    int i;

    if (info->argc == 1)
    {
        _eputs("Too few arguments.\n"); /* Print an error message for too few arguments. */
        return (1);
    }
    for (i = 1; i <= info->argc; i++)
        _unsetenv(info, info->argv[i]); /* Unset (remove) the specified environment variable. */

    return (0);
}





/**
 * populate_env_list - Add environment variables to the linked list.
 *
 * @info: Structure containing potential arguments. Used to maintain
 *        a consistent function prototype.
 *
 * Return: Always 0.
 */



/*function populate_env_list*/
int populate_env_list(info_t *info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        add_node_end(&node, environ[i], 0); /* Add each environment variable to the linked list. */
    info->env = node; /* Update the environment variable list in the info structure. */
    return (0);
}

