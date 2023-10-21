#include "shell.h"




/**
 * my_strcpy - custom string copy function
 * @dest: the destination string to copy into
 * @src: the source string to be copied
 *
 * Return: a pointer to the final string
 */




/*my_strcpy*/
char *my_strcpy(char *dest, char *src)
{
    int len = 0, i = 0;

    len = 0;

    /* Calculate the length of the source string */
    while (src[len] != '\0')
        len++;

    /* Copy characters from the source string to the destination string */
    for (; i < len; i++)
        dest[i] = src[i];

    dest[i] = '\0';

    /* Return a pointer to the final string */
    return (dest);
}
