#include "shell.h"



/**
 * my_strlen - custom string length function
 * @str: input string
 * Return: the length of the string
 */
size_t my_strlen(const char *str);/*my_strlen*/



/**
 * my_getline - custom implementation of the getline function
 * @line: pointer to the line buffer
 * @len: pointer to the length of the buffer
 * @stream: stream to read from
 * Return: the number of characters read or -1 if an error occurs
 */


/*my_getline*/
ssize_t my_getline(char **line, size_t *len, FILE *stream)
{
    char *getline;  /* Temporary buffer for reading */
    ssize_t read;   /* Number of characters read */

    /* If the line buffer is not initialized or its length is 0 */
    if (*line == NULL || *len == 0)
    {
        *len = 1024; /* Set the initial buffer size to 1024 */
        *line = malloc(*len); /* Allocate memory for the line buffer */
        if (*line == NULL)
        {
            return (-1); /* Return -1 if allocation fails */
        }
    }

    getline = fgets(*line, *len, stream); /* Read a line from the stream */

    if (getline != NULL) /* If reading was successful */
    {
        read = my_strlen(*line); /* Determine the length of the line */

        if (read > 0 && (*line)[read - 1] == '\n')
        {
            (*line)[read - 1] = '\0'; /* Remove the newline character if present */
            read--;
        }
        return (read); /* Return the number of characters read */
    }
    else
    {
        return (-1); /* Return -1 to indicate an error */
    }
}

