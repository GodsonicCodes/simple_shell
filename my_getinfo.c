#include "shell.h"



/**
 * clear_info - Initializes an info_t struct with default values.
 * @info: Address of the info_t struct to be initialized.
 *
 * This function is responsible for initializing an info_t struct. It sets several fields
 * to default values, including setting 'arg', 'argv', and 'path' to NULL, and 'argc' to 0.
 */



/*function clear_info*/
void clear_info(info_t *info)
{
    info->arg = NULL; /* Initialize 'arg' to NULL */
    info->argv = NULL; /* Initialize 'argv' to NULL */
    info->path = NULL; /* Initialize 'path' to NULL */
    info->argc = 0; /* Set 'argc' to 0 (no arguments) */
}




/**
 * set_info - Initializes an info_t struct with command line arguments.
 * @info: Address of the info_t struct to be initialized.
 * @av: Argument vector containing command line arguments.
 *
 * This function initializes an info_t struct with the provided command line arguments. It assigns
 * the 'fname' field with the first element of the 'av' argument vector. If 'info->arg' is not NULL,
 * it parses the command line arguments, creates an 'argv' array, and updates 'argc' with the number
 * of arguments. Additionally, it performs alias and variable replacement on the command.
 */



/*function set_info*/
void set_info(info_t *info, char **av)
{
    int i = 0;

    info->fname = av[0]; /* Assign 'fname' to the first element of 'av' */

    if (info->arg)
    {
        info->argv = strtow(info->arg, " \t"); /* Parse 'arg' into 'argv' using ' ' and '\t' delimiters */
        if (!info->argv)
        {
            info->argv = malloc(sizeof(char *) * 2); /* Allocate memory for 'argv' */
            if (info->argv)
            {
                info->argv[0] = _strdup(info->arg); /* Duplicate 'arg' into 'argv[0]' */
                info->argv[1] = NULL; /* Set 'argv[1]' to NULL */
            }
        }

        for (i = 0; info->argv && info->argv[i]; i++)
            ;
        info->argc = i; /* Update 'argc' with the number of arguments */

         /*Perform alias and variable replacement*/
        replace_alias(info); /* Perform alias replacement on the command */
        replace_vars(info); /* Perform variable replacement on the command */
    }
}




/**
 * free_info - Frees specific fields in an info_t struct, optionally all fields.
 * @info: Address of the info_t struct.
 * @all: Flag indicating whether to free all fields (if true) or only specific fields.
 *
 * This function is responsible for freeing specific fields in the info_t struct.
 * If 'all' is true, it can free additional fields such as environment variables, history, aliases,
 * the command buffer, environment variable array, and closes the 'readfd' if it's greater than 2.
 */




/*function free_info*/
void free_info(info_t *info, int all)
{
    ffree(info->argv); /* Free 'argv' */
    info->argv = NULL;
    info->path = NULL; /* Set 'path' to NULL */

    if (all)
    {
        if (!info->cmd_buf)
            free(info->arg); /* Free 'arg' if 'cmd_buf' is not set */

        if (info->env)
            free_list(&(info->env)); /* Free environment variables list */

        if (info->history)
            free_list(&(info->history)); /* Free command history list */

        if (info->alias)
            free_list(&(info->alias)); /* Free alias list */

        ffree(info->environ); /* Free environment variable array */
        info->environ = NULL;

        bfree((void **)info->cmd_buf); /* Free the command buffer */

        if (info->readfd > 2)
            close(info->readfd); /* Close 'readfd' if it's greater than 2 */

        _putchar(BUF_FLUSH); /* Flush the output buffer */
    }
}

