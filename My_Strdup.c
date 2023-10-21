#include "shell.h"

size_t my_strlen(const char *str); /*my_strlen*/


/**
 * my_strdup - custom string duplication function
 * @str: the string to be duplicated
 *
 * Return: a new duplicated string or NULL on failure
 */



/*my_strdup*/
char *my_strdup(const char *str)
{
    size_t length = my_strlen(str) + 1;
    char *new_str = (char *)malloc(length); /*Allocate memory for the new string*/
    size_t i = 0;

    if (new_str == NULL)
        return (NULL); /*Return NULL if memory allocation fails*/

    /*Copy characters from the source string to the new duplicated string*/
    for (; i < length; i++)
        new_str[i] = str[i];

    /*Return a pointer to the new duplicated string*/
    return (new_str);
}
