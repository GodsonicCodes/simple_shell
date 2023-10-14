#include "shell.h"




/**
 * These functions include _memset, ffree, and _realloc.
 *
 * _memset - Fills memory with a constant byte.
 * @s: The pointer to the memory area.
 * @b: The byte to fill *s with.
 * @n: The number of bytes to be filled.
 * Return: (s) A pointer to the memory area s.
 *
 * ffree - Frees a string of strings.
 * @pp: The string of strings to be freed.
 *
 * _realloc - Reallocates a block of memory.
 * @ptr: Pointer to the previous malloc'ated block.
 * @old_size: Byte size of the previous block.
 * @new_size: Byte size of the new block.
 * Return: Pointer to the old block or a new one if reallocated.
 */



/*function _memset*/
char *_memset(char *s, char b, unsigned int n)
{
    unsigned int i;

    /* Loop through the memory area and set each byte to 'b'. */
    for (i = 0; i < n; i++)
        s[i] = b;
    return (s);
}





/**
 * ffree - Frees a string of strings.
 * @pp: The string of strings to be freed.
 */



/*function ffree*/
void ffree(char **pp)
{
    char **a = pp;

    /* Check if the input is NULL to avoid errors. */
    if (!pp)
        return;
    
    /* Free each string in the array and then free the array itself. */
    while (*pp)
        free(*pp++);
    free(a);
}




/**
 * _realloc - Reallocates a block of memory.
 * @ptr: Pointer to the previous malloc'ated block.
 * @old_size: Byte size of the previous block.
 * @new_size: Byte size of the new block.
 * Return: Pointer to the old block or a new one if reallocated.
 */




/*function _realloc*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *p;

    /* If 'ptr' is NULL, simply allocate a new block of 'new_size'. */
    if (!ptr)
        return (malloc(new_size);

    /* If 'new_size' is zero, free the previous block and return NULL. */
    if (!new_size)
        return (free(ptr), NULL);

    /* If 'new_size' is the same as 'old_size', return 'ptr' as is. */
    if (new_size == old_size)
        return (ptr);

    /* Allocate a new block of 'new_size', copy data, and free the old block. */
    p = malloc(new_size);
    if (!p)
        return (NULL);

    old_size = old_size < new_size ? old_size : new_size;
    while (old_size--)
        p[old_size] = ((char *)ptr)[old_size];
    free(ptr);
    return (p);
}

