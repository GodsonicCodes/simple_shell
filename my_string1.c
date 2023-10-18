#include "shell.h"




/**
 * _strcpy - Copy a string from source to destination.
 * @dest: The destination string.
 * @src: The source string.
 *
 * Return: Pointer to the destination string.
 */



/*function _strcpy*/
char *_strcpy(char *dest, char *src)
{
    int i = 0;

    /* Check if source and destination are the same or source is NULL */
    if (dest == src || src == 0)
        return (dest);

    /* Copy characters from source to destination */
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = 0;  /* Null-terminate the destination string */
    return (dest);
}




/**
 * _strdup - Duplicate a string.
 * @str: The string to duplicate.
 *
 * Return: Pointer to the duplicated string.
 */



/*function _strdup*/
char *_strdup(const char *str)
{
    int length = 0;
    char *ret;

    /* Check if the input string is NULL */
    if (str == NULL)
        return (NULL);

    /* Calculate the length of the string */
    while (*str++)
        length++;

    /* Allocate memory for the duplicated string */
    ret = malloc(sizeof(char) * (length + 1));

    /* Check for memory allocation failure */
    if (!ret)
        return (NULL);

    /* Copy the string in reverse order to the duplicated string */
    for (length++; length--;)
        ret[length] = *--str;

    return (ret);
}




/**
 * _puts - Print an input string.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */



/*function _puts*/
void _puts(char *str)
{
    int i = 0;

    /* Check if the input string is NULL */
    if (!str)
        return;

    /* Print each character of the string */
    while (str[i] != '\0')
    {
        _putchar(str[i]);
        i++;
    }
}




/**
 * _putchar - Write the character c to stdout.
 * @c: The character to print.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */



/*function _putchar*/
int _putchar(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    /* Check for buffer flush or buffer full */
    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        /* Write the buffer to stdout and reset the buffer */
        write(1, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;  /* Add character to the buffer */
    return (1);
}

