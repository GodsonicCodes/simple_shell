#include "shell.h"



/**
 * interactive - Determines whether the shell is running in interactive mode.
 *
 * @info: A pointer to the struct that contains various information.
 *
 * Return: 1 if the shell is in interactive mode, 0 otherwise.
 */


/*function interactive*/
int interactive(info_t *info)
{
    /* Check if the standard input (file descriptor 0) is associated with a terminal,
       and if the 'readfd' field in 'info' is less than or equal to 2. */
    return (isatty(STDIN_FILENO) && info->readfd <= 2);
}



/**
 * is_delim - Checks if a character is a delimiter.
 *
 * @c: The character to be checked.
 * @delim: The string containing delimiter characters.
 *
 * Return: 1 if the character is a delimiter, 0 if it's not.
 */


/*function is_delim*/
int is_delim(char c, char *delim)
{
    /* Iterate through the 'delim' string to check if 'c' matches any character in 'delim'. */
    while (*delim)
    {
        if (*delim++ == c)
            return (1); /* Return 1 if 'c' is a delimiter. */
    }
    return (0); /* Return 0 if 'c' is not a delimiter. */
}




/**
 * _isalpha - Checks if a character is alphabetic (a letter).
 *
 * @c: The character to be checked.
 *
 * Return: 1 if 'c' is an alphabetic character, 0 otherwise.
 */


/*function _isalpha*/
int _isalpha(int c)
{
    /* Check if 'c' is in the range of lowercase letters (a to z) or uppercase letters (A to Z). */
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (1); /* Return 1 if 'c' is an alphabetic character. */
    else
        return (0); /* Return 0 if 'c' is not an alphabetic character. */
}



/**
 * _atoi - Converts a string to an integer.
 *
 * @s: The string to be converted to an integer.
 *
 * Return: 0 if there are no numbers in the string, the converted number otherwise.
 */



/*function _atoi*/
int _atoi(char *s)
{
    int i, sign = 1, flag = 0, output;
    unsigned int result = 0;

    /* Iterate through the characters in the 's' string and convert it to an integer. */
    for (i = 0; s[i] != '\0' && flag != 2; i++)
    {
        /* Check if the character is a minus sign to determine the sign of the number. */
        if (s[i] == '-')
            sign *= -1;

        /* Check if the character is a digit (0-9) and convert it to an integer. */
        if (s[i] >= '0' && s[i] <= '9')
        {
            flag = 1; /* Set 'flag' to 1 to indicate that at least one digit has been found. */
            result *= 10;
            result += (s[i] - '0'); /* Convert the character to an integer and add it to 'result'. */
        }
        else if (flag == 1)
            flag = 2; /* Set 'flag' to 2 to indicate the end of the number. */
    }

    /* Adjust the result based on the sign and return the final converted integer. */
    if (sign == -1)
        output = -result;
    else
        output = result;

    return (output); /* Return the converted integer. */
}

