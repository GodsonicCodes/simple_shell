#include "shell.h"
#include <signal.h>




/**
 * input_buf - Buffers chained commands.
 *
 * @info: The parameter struct.
 * @buf: Address of the buffer.
 * @len: Address of the len var.
 *
 * This function buffers chained commands. If there's nothing left in the buffer,
 * it reads input from the user. If the input is a command chain separated by ';',
 * it handles it accordingly.
 *
 * Return: The number of bytes read.
 */



/*function input_buf*/
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
    ssize_t r = 0;
    size_t len_p = 0;

    if (!*len) /* If nothing left in the buffer, fill it */
    {
        /* Clear the buffer and set it to NULL */
        free(*buf);
        *buf = NULL;
        r = _getline(info, buf, &len_p);  /* Read a line from stdin using custom _getline */
        if (r > 0)
        {
            if ((*buf)[r - 1] == '\n')
            {
                (*buf)[r - 1] = '\0'; /* Remove trailing newline */
                r--;
            }
            info->linecount_flag = 1;
            remove_comments(*buf);  /* Remove comments from the input line */
            build_history_list(info, *buf, info->histcount++);  /* Build a history list */
            /* if (_strchr(*buf, ';')) is this a command chain? */
            {
                *len = r;
                info->cmd_buf = buf;
            }
        }
    }
    return (r);
}




/**
 * _getline - Gets the next line of input from STDIN.
 *
 * @info: The parameter struct.
 * @ptr: Address of a pointer to a buffer, preallocated or NULL.
 * @length: The size of the preallocated ptr buffer if not NULL.
 *
 * Return: The value of s.
 */



/*fucntion _getline*/
ssize_t _getline(info_t *info, char **ptr, size_t *length)
{
    static char buf[READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t r = 0, s = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length)
        s = *length;
    if (i == len)
        i = len = 0;

    r = read_buf(info, buf, &len);
    if (r == -1 || (r == 0 && len == 0))
        return (-1);

    c = _strchr(buf + i, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : len;
    new_p = _realloc(p, s, s ? s + k : k + 1);
    if (!new_p) /* MALLOC FAILURE! */
        return (p ? free(p), -1 : -1);

    if (s)
        _strncat(new_p, buf + i, k - i);
    else
        _strncpy(new_p, buf + i, k - i + 1);

    s += k - i; /* Increment the total length by the difference. */
    i = k; /* Update the iterator position. */
    p = new_p; /* Update the pointer to the buffer. */

    if (length)
        *length = s; /* Update the length if provided. */
    *ptr = p; /* Update the pointer to the buffer. */
    return (s); /* Return the total length. */
}





/**
 * sigintHandler - Blocks Ctrl-C.
 *
 * @sig_num: The signal number.
 *
 * This function handles the SIGINT signal, effectively blocking Ctrl-C.
 *
 * Return: Void.
 */



/*function sigintHander*/
void sigintHandler(__attribute__((unused)) int sig_num)
{
    _puts("\n"); /* Print a newline character. */
    _puts("$ "); /* Print the shell prompt. */
    _putchar(BUF_FLUSH); /* Flush the character buffer. */
}


