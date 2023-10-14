#include <limits.h>
#include "shell.h"



/**
 * _erratoi - This Converts a string to an integer.
 *
 * @s: Is The string to be converted.
 *
 * This function attempts to convert a string to an integer.

 * Return: 0 if there are no numbers in the string, the converted number otherwise, and -1 on error.
 */




/*function _erratoi*/
int _erratoi(char *s)
{
    int i = 0;
    unsigned long int result = 0;

    if (*s == '+')
        s++;  /* Skip the leading plus sign (if any). */
    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            result *= 10;
            result += (s[i] - '0');
            if (result > INT_MAX)
                return -1; /* Overflow: return -1 on error. */
        }
        else
            return -1; /* Invalid character in the string: return -1 on error. */
    }
    return (int)result;
}




/**
 * print_error - This Prints an error message.
 *
 * @info: Is The parameter and return info struct.
 * @estr: Is The String containing the specified error type.
 *
 * This function prints an error message to standard error (stderr).

 * Return: None.
 */


/*function print_error*/
void print_error(info_t *info, char *estr)
{
    _eputs(info->fname); /* Print the program name. */
    _eputs(": ");
    print_d(info->line_count, STDERR_FILENO); /* Print the line number. */
    _eputs(": ");
    _eputs(info->argv[0]); /* Print the command name. */
    _eputs(": ");
    _eputs(estr); /* Print the specified error message. */
}




/**
 * print_d - Prints a decimal (integer) number (base 10).
 *
 * @input: The input number.
 * @fd: The file descriptor to write to.
 *
 * This function prints a decimal (integer) number to the specified file descriptor.

 * Return: The number of characters printed.
 */



/*function print_d*/
int print_d(int input, int fd)
{
    int (*__putchar)(char) = _putchar;
    int i, count = 0;
    unsigned int _abs_, current;

    if (fd == STDERR_FILENO)
        __putchar = _eputchar; /* Use _eputchar for stderr. */
    if (input < 0)
    {
        _abs_ = -input;
        __putchar('-'); /* Print a minus sign for negative numbers. */
        count++;
    }
    else
        _abs_ = input;
    current = _abs_;
    for (i = 1000000000; i > 1; i /= 10)
    {
        if (_abs_ / i)
        {
            __putchar('0' + current / i); /* Print the digits of the number. */
            count++;
        }
        current %= i;
    }
    __putchar('0' + current);
    count++;

    return count;
}





/**
 * convert_number - Our Converter function, a clone of itoa.
 *
 * @num: The number.
 * @base: The base for conversion.
 * @flags: Argument flags.
 *
 * This function converts a number to a string using the specified base.

 * Return: The converted string.
 */



/*function *convert_number*/
char *convert_number(long int num, int base, int flags)
{
    static char *array;
    static char buffer[50];
    char sign = 0;
    char *ptr;
    unsigned long n = num;

    if (!(flags & CONVERT_UNSIGNED) && num < 0)
    {
        n = -num;
        sign = '-'; /* Set the sign for negative numbers. */
    }
    array = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buffer[49];
    *ptr = '\0';

    do
    {
        *--ptr = array[n % base]; /* Convert and store each digit in reverse order. */
        n /= base;
    } while (n != 0);

    if (sign)
        *--ptr = sign; /* Add the sign character for negative numbers. */
    return ptr;
}





/**
 * remove_comments - Replaces the first instance of '#' with '\0'.
 *
 * @buf: The address of the string to modify.
 *
 * This function searches for the first '#' character in the string and replaces it with '\0'.

 * Return: Always 0.
 */



/*function remove_comments*/
void remove_comments(char *buf)
{
    int i;

    for (i = 0; buf[i] != '\0'; i++)
    {
        if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
        {
            buf[i] = '\0'; /* Replace the '#' with null character to remove comments. */
            break;
        }
    }
}

