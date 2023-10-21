#include "shell.h"



/**
 * my_strcmp - custom string comparison function
 * @string1: the first string to compare
 * @string2: the second string to compare
 *
 * Return: an integer value representing the comparison result
 */



/*my_strcmp*/
int my_strcmp(const char *string1, const char *string2)
{
    /* Compare the characters in string1 and string2 until a difference is found */
    while (*string1 && *string2 && *string1 == *string2)
    {
        string1++;
        string2++;
    }

    /* Return an integer representing the result of the comparison */
    return (int)(*string1 - *string2);
}
