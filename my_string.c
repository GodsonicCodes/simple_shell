#include "shell.h"



/**
 * _strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: An integer representing the length of the input string 's'.
 */


/*function _strlen*/
int _strlen(char *s)
{
    int i = 0;

    if (!s)  /* Check if the input string is NULL. */
        return (0);

    while (*s++)  /* Iterate through the string until the null-terminator is reached. */
        i++;
    return (i);  /* Return the length of the string. */
}





/**
 * _strcmp - performs lexicographic comparison of two strings
 * @s1: the first string to compare
 * @s2: the second string to compare
 *
 * Return: A negative value if 's1' comes before 's2', a positive value if 's1' comes after 's2',
 *         and zero if 's1' is equal to 's2'.
 */



/*function _strcmp*/
int _strcmp(char *s1, char *s2)
{
    while (*s1 && *s2)  /* Iterate through both strings until the end of either string is reached. */
    {
        if (*s1 != *s2)  /* Compare characters of both strings. */
            return (*s1 - *s2);  /* Return the difference if characters are not equal. */
        s1++;
        s2++;
    }
    if (*s1 == *s2)  /* Check if both strings are equal at this point. */
        return (0);
    else
        return (*s1 < *s2 ? -1 : 1);  /* Return a negative or positive value based on comparison. */
}




/**
 * starts_with - checks if 'needle' starts with 'haystack'
 * @haystack: the string to search
 * @needle: the substring to find
 *
 * Return: The address of the next character in 'haystack' if 'needle' starts with 'haystack', 
 *         or NULL if 'needle' doesn't start with 'haystack'.
 */


/*function starts_with*/
char *starts_with(const char *haystack, const char *needle)
{
    while (*needle)  /* Iterate through 'needle' characters. */
    {
        if (*needle++ != *haystack++)  /* Compare characters of 'needle' and 'haystack'. */
            return (NULL);  /* Return NULL if there's a mismatch. */
    }
    return ((char *)haystack);  /* Return the address of the next character in 'haystack'. */
}




/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: A pointer to the destination buffer (the concatenated string).
 */



/*function _strcat*/
char *_strcat(char *dest, char *src)
{
    char *ret = dest;  /* Store the original address of the destination buffer. */

    while (*dest)  /* Iterate through 'dest' until the null-terminator is reached. */
        dest++;
    while (*src)  /* Iterate through 'src'. */
        *dest++ = *src++;  /* Copy characters from 'src' to 'dest'. */
    *dest = *src;  /* Append the null-terminator to 'dest'. */
    return (ret);  /* Return the concatenated string. */
}

