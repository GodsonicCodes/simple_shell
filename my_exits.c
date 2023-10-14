#include "shell.h"



/**
 * _strncpy - Copies a string.
 *
 * @dest: The destination string to be copied to.
 * @src: The source string.
 * @n: The maximum number of characters to be copied.
 *
 * This function copies the first 'n' characters from the source string 'src'
 * to the destination string 'dest'. It ensures that 'dest' is null-terminated.
 *
 * Return: The concatenated string.
 */


/*function *_strncpy*/
char *_strncpy(char *dest, char *src, int n)
{
    int i, j;
    char *s = dest;

    i = 0;
    while (src[i] != '\0' && i < n - 1)
    {
        dest[i] = src[i];
        i++;
    }
    if (i < n)
    {
        j = i;
        while (j < n)
        {
            dest[j] = '\0'; /* Null-terminate the destination string. */
            j++;
        }
    }
    return (s);
}





/**
 * _strncat - This Concatenates two strings.
 *
 * @dest: The first string.
 * @src: The second string.
 * @n: The maximum number of bytes to be used from 'src'.
 *
 * This function concatenates the first 'n' characters from 'src' to the end of 'dest'.
 * It ensures that 'dest' remains null-terminated.
 *
 * Return: The concatenated string.
 */




/*function *_strncat*/
char *_strncat(char *dest, char *src, int n)
{
    int i, j;
    char *s = dest;

    i = 0;
    j = 0;
    while (dest[i] != '\0')
        i++;
    while (src[j] != '\0' && j < n)
    {
        dest[i] = src[j];
        i++;
        j++;
    }
    if (j < n)
        dest[i] = '\0'; /* Null-terminate 'dest'. */
    return (s);
}




/**
 * _strchr - Locates a character in a string.
 *
 * @s: The string to be parsed.
 * @c: The character to look for.
 *
 * This function searches for the character 'c' in the string 's'.
 * If found, it returns a pointer to the memory area within 's' where 'c' is located.
 *
 * Return: A pointer to the memory area within 's' where 'c' is located.
 */



/*function *_strchr*/
char *_strchr(char *s, char c)
{
    do
    {
        if (*s == c)
            return (s); /* Found the character 'c' in the string 's'. */
    } while (*s++ != '\0');

    return (NULL); /* Character 'c' was not found in the string 's'. */
}

