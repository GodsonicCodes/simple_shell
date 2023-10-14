#include "shell.h"




/**
 * _eputs - Print an input string to standard error.
 *
 * @str: The string to be printed.
 *
 * This function is used to print a string to the standard error (stderr) stream.
 * It iterates through each character of the input string and prints it to stderr.

 * Return: Nothing.
 */



/* function _eputs*/
void _eputs(char *str)
{
    int i = 0;

    if (!str) /* Check if the input string is NULL. */
        return;
    while (str[i] != '\0') /* Loop through the string until the null terminator is reached. */
    {
        _eputchar(str[i]); /* Call _eputchar to print each character to standard error. */
        i++;
    }
}




/**
 * _eputchar - Write the character 'c' to the standard error (stderr).
 *
 * @c: The character to print.
 *
 * This function writes a character to the standard error (stderr). It uses a
 * static buffer to accumulate characters before writing them to stderr in chunks.

 * Return: On success, 1. On error, -1 is returned, and errno is set appropriately.
 */


/*function _eputchar*/
int _eputchar(char c)
{
    static int i; /* Static variable to maintain the buffer index. */
    static char buf[WRITE_BUF_SIZE]; /* Static character buffer for accumulating characters. */

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE) /* Check if the character should be flushed or if the buffer is full. */
    {
        write(2, buf, i); /* Write the buffer to standard error (file descriptor 2). */
        i = 0;
    }
    if (c != BUF_FLUSH) /* If the character is not a flush command. */
        buf[i++] = c; /* Store the character in the buffer. */
    return (1); /* Return 1 to indicate success. */
}




/**
 * _putfd - Write the character 'c' to the given file descriptor (fd).
 *
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * This function writes a character to the specified file descriptor (fd). It
 * uses a static buffer to accumulate characters before writing them to the file descriptor.

 * Return: On success, 1. On error, -1 is returned, and errno is set appropriately.
 */



/*function _putfd*/
int _putfd(char c, int fd)
{
    static int i; /* Static variable to maintain the buffer index. */
    static char buf[WRITE_BUF_SIZE]; /* Static character buffer for accumulating characters. */

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE) /* Check if the character should be flushed or if the buffer is full. */
    {
        write(fd, buf, i); /* Write the buffer to the specified file descriptor (fd). */
        i = 0;
    }
    if (c != BUF_FLUSH) /* If the character is not a flush command. */
        buf[i++] = c; /* Store the character in the buffer. */
    return (1); /* Return 1 to indicate success. */
}




/**
 * _putsfd - Print an input string to the given file descriptor (fd).
 *
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * This function writes a string to the specified file descriptor (fd). It
 * iterates through the string and calls _putfd to write each character to the file descriptor.

 * Return: The number of characters written.
 */



/*function _putsfd*/
int _putsfd(char *str, int fd)
{
    int i = 0;

    if (!str) /* Check if the input string is NULL. */
        return (0);
    while (*str) /* Loop through the string until the null terminator is reached. */
    {
        i += _putfd(*str++, fd); /* Call _putfd to write each character to the specified file descriptor (fd). */
    }
    return i; /* Return the number of characters written. */
}
