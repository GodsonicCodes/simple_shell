#include "shell.h"



/**
 * is_chain - Test if the current character in the buffer is a chain delimiter.
 *
 * @p: pointer to the current position in the buffer.
 * @info: the parameter struct containing various information.
 * @buf: the character buffer containing the input string.
 * Return: 1 if it's a chain delimiter, 0 otherwise.
 */




/* is_chain function */
int is_chain(info_t *info, char *buf, size_t *p)
{
    size_t j = *p;

    /* Check for '||' chain delimiter */
    if (buf[j] == '|' && buf[j + 1] == '|')
    {
        buf[j] = 0; /* Replace '|' with null character to terminate the previous command. */
        j++;
        info->cmd_buf_type = CMD_OR; /* Set the command buffer type to OR. */
    }
    /* Check for '&&' chain delimiter */
    else if (buf[j] == '&' && buf[j + 1] == '&')
    {
        buf[j] = 0; /* Replace '&' with null character to terminate the previous command. */
        j++;
        info->cmd_buf_type = CMD_AND; /* Set the command buffer type to AND. */
    }
    /* Check for ';' chain delimiter (end of a command) */
    else if (buf[j] == ';')
    {
        buf[j] = 0; /* Replace ';' with null character to terminate the previous command. */
        info->cmd_buf_type = CMD_CHAIN; /* Set the command buffer type to CHAIN. */
    }
    else
        return (0);

    *p = j; /* Update the current position pointer. */
    return (1);
}




/**
 * check_chain - Checks if we should continue chaining based on the last status.
 *
 * @info: the parameter struct containing various information.
 * @buf: the character buffer containing the input string.
 * @p: pointer to the current position in the buffer.
 * @i: starting position in the buffer.
 * @len: length of the buffer.
 *
 * Return: Void
 */





/* check_chain function */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
    size_t j = *p;

    /* Check if the previous command used the AND operator and the status is true. */
    if (info->cmd_buf_type == CMD_AND)
    {
        if (info->status)
        {
            buf[i] = 0; /* Terminate the previous command with a null character. */
            j = len; /* Set the current position pointer to the end of the buffer. */
        }
    }
    /* Check if the previous command used the OR operator and the status is false. */
    if (info->cmd_buf_type == CMD_OR)
    {
        if (!info->status)
        {
            buf[i] = 0; /* Terminate the previous command with a null character. */
            j = len; /* Set the current position pointer to the end of the buffer. */
        }
    }

    *p = j; /* Update the current position pointer. */
}




/**
 * replace_alias - Replaces an alias in the tokenized string.
 *
 * @info: the parameter struct containing various information.
 *
 * Return: 1 if replaced, 0 otherwise.
 */




/* replace_alias function */
int replace_alias(info_t *info)
{
    int i;
    list_t *node;
    char *p;

    for (i = 0; i < 10; i++)
    {
        /* Find an alias that matches the first argument in the command. */
        node = node_starts_with(info->alias, info->argv[0], '=');
        if (!node)
            return (0);
        free(info->argv[0]);
        p = _strchr(node->str, '=');
        if (!p)
            return (0);
        p = _strdup(p + 1);
        if (!p)
            return (0);
        info->argv[0] = p;
    }
    return (1);
}




/**
 * replace_vars - Replaces variables in the tokenized string.
 *
 * @info: the parameter struct containing various information.
 *
 * Return: 1 if replaced, 0 otherwise.
 */




/* replace_vars function */
int replace_vars(info_t *info)
{
    int i = 0;
    list_t *node;

    for (i = 0; info->argv[i]; i++)
    {
        /* Check if the argument starts with '$' and is not empty. */
        if (info->argv[i][0] != '$' || !info->argv[i][1])
            continue;

        /* Replace specific variable references in the argument. */
        if (!_strcmp(info->argv[i], "$?"))
        {
            replace_string(&(info->argv[i]), _strdup(convert_number(info->status, 10, 0)));
            continue;
        }
        if (!_strcmp(info->argv[i], "$$"))
        {
            replace_string(&(info->argv[i]), _strdup(convert_number(getpid(), 10, 0)));
            continue;
        }
        node = node_starts_with(info->env, &info->argv[i][1], '=');
        if (node)
        {
            replace_string(&(info->argv[i]), _strdup(_strchr(node->str, '=') + 1));
            continue;
        }
        replace_string(&info->argv[i], _strdup("")); /* Replace the variable with an empty string. */
    }
    return (0);
}




/**
 * replace_string - Replaces a string.
 *
 * @old: Address of the old string.
 * @new: New string.
 *
 * Return: 1 if replaced, 0 otherwise.
 */




/* replace_string function */
int replace_string(char **old, char *new)
{
    free(*old); /* Free the memory of the old string. */
    *old = new; /* Update the pointer to the new string. */
    return (1);
}

