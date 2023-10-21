#include "shell.h"




/**
 * my_strlen - custom string length function
 * @str: the input string
 *
 * Return: the number of characters in the string
 */




/*my_strlen*/
size_t my_strlen(const char *str)
{
    size_t i = 0;

    /* Initialize the character count to zero */
    while (str[i] != '\0')
        i++;

    /* Return the total number of characters in the string */
    return (i);
}

