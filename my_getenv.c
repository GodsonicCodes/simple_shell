#include "shell.h"
#include <signal.h> /*Include the <signal.h> header for 'signal' and 'SIGINT'*/



/**
 * get_environ - Returns a copy of the environment variables.
 *
 * @info: Structure containing potential arguments, used to maintain
 *        constant function prototype.
 *
 * This function checks if the environment variables have changed and updates
 * the environ variable accordingly.
 *
 * Return: A string array representing the environment variables.
 */



/*function **get_environ*/
char **get_environ(info_t *info)
{
    char **buf = NULL;
    ssize_t r = 0;
    size_t len_p = 0;

    if (!info->environ || info->env_changed)
    {
        if (buf)
        {
            free(*buf); /* If nothing left in the buffer, free it */
            *buf = NULL; /* Clear the buffer and set it to NULL */
        }
        signal(SIGINT, sigintHandler); /* Set a signal handler for Ctrl-C */
#if USE_GETLINE
        r = getline(buf, &len_p, stdin); /* Read a line from stdin using getline */
#else
        r = _getline(info, buf, &len_p); /* Read a line from stdin using custom _getline */
#endif
        if (r > 0)
        {
            if ((*buf)[r - 1] == '\n')
            {
                (*buf)[r - 1] = '\0'; /* Remove the trailing newline character */
                r--;
            }
            info->linecount_flag = 1;
            remove_comments(*buf); /* Remove comments from the input line */
            build_history_list(info, *buf, info->histcount++); /* Build a history list */
            {
                len_p = r;
                info->cmd_buf = buf;
            }
        }
    }
    return info->cmd_buf;
}




/**
 * _unsetenv - Remove an environment variable.
 *
 * @info: Structure containing potential arguments, used to maintain
 *        constant function prototype.
 * @var: The string representing the environment variable property.
 *
 * This function iterates through the environment variables to find and
 * remove the specified variable.
 *
 * Return: 1 if the variable is deleted, 0 otherwise.
 */




/*function _unsetenv*/
int _unsetenv(info_t *info, char *var)
{
    list_t *node = info->env;  /* Create a pointer to the environment linked list. */
    size_t i = 0;  /* Initialize a counter for the node index. */
    char *p;  /* Create a pointer for parsing the environment variables. */

    if (!node || !var)
        return (0);  /* Return 0 indicating the variable was not deleted. */

    while (node)
    {
        p = starts_with(node->str, var);  /* Parse the current environment variable. */
        if (p && *p == '=')
        {
            info->env_changed = delete_node_at_index(&(info->env), i);  /* Delete the node at the current index, which removes the variable. */
            i = 0;  /* Reset the node index. */
            node = info->env;  /* Start from the beginning of the linked list. */
            continue;
        }
        node = node->next;  /* Move to the next environment variable. */
        i++;  /* Increment the node index. */
    }
    return (info->env_changed);  /* Return whether the environment has been changed. */
}





/**
 * _setenv - Initialize a new environment variable or modify an existing one.
 *
 * @info: Structure containing potential arguments, used to maintain
 *        constant function prototype.
 * @var: The string representing the environment variable property.
 * @value: The string representing the environment variable value.
 *
 * This function creates a new environment variable or updates an existing one
 * by modifying the linked list of environment variables.
 *
 * Return: Always 0.
 */



/*function _setenv*/
int _setenv(info_t *info, char *var, char *value)
{
    char *buf = NULL;  /* Create a pointer for the environment variable string. */
    list_t *node;  /* Create a pointer to traverse the environment linked list. */
    char *p;  /* Create a pointer for parsing the environment variables. */

    if (!var || !value)
        return (0);  /* If the variable name or value is not provided, return 0. */

    buf = malloc(_strlen(var) + _strlen(value) + 2);  /* Allocate memory for the environment variable string. */
    if (!buf)
        return (1);  /* If memory allocation fails, return 1. */

    _strcpy(buf, var);  /* Create the environment variable string by combining the name and value. */
    _strcat(buf, "=");
    _strcat(buf, value);

    node = info->env;  /* Initialize the node pointer to the beginning of the environment linked list. */

    while (node)
    {
        p = starts_with(node->str, var);  /* Parse the current environment variable. */
        if (p && *p == '=')
        {
            free(node->str);  /* Free the current environment variable string. */
            node->str = buf;  /* Update the node's string to the new environment variable string. */
            info->env_changed = 1;  /* Set the environment change flag to 1. */
            return (0);  /* Return 0 to indicate success. */
        }
        node = node->next;  /* Move to the next environment variable. */
    }

    add_node_end(&(info->env), buf, 0);  /* If the variable was not found, add it to the end of the linked list. */
    free(buf);  /* Free the temporary buffer used for the new environment variable. */
    info->env_changed = 1;  /* Set the environment change flag to 1. */
    return (0);  /* Return 0 to indicate success. */
}

