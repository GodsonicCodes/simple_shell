#include "shell.h"




/**
 * my_strcat - custom string concatenation function
 * @final_str: pointer to the string to which another string will be appended
 * @str_to: pointer to the string to be added
 *
 * Return: a pointer to the resulting string after concatenation
 */




/*my_strcat*/
char *my_strcat(char *final_str, char *str_to)
{
    int i, j;  /* Index variables for final_str and str_to */

    i = 0;  /* Initialize the index for final_str */

    while (final_str[i] != '\0')
        i++;  /* Move to the end of final_str */

    j = 0;  /* Initialize the index for str_to */

    while (str_to[j] != '\0')
    {
        final_str[i] = str_to[j];  /* Copy characters from str_to to final_str */
        j++;
        i++;
    }
    final_str[i] = '\0';  /* Add a null terminator to the resulting string */

    return final_str;  /* Return a pointer to the concatenated string */
}

