#include "shell.h"





/**
 * _realloc - Reallocates a block of memory.
 * @ptr: Pointer to the previous malloc'ated block.
 * @new_size: Byte size of the new block.
 * Return: Pointer to the old block or a new one if reallocated.
 */





/* function _realloc */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *p;
    unsigned int copy_size;

    /* If 'ptr' is NULL, simply allocate a new block of 'new_size'. */
    if (!ptr)
        return malloc(new_size);

    /* If 'new_size' is zero, free the previous block and return NULL. */
    if (!new_size)
    {
        free(ptr);
        return NULL;
    }

    /* If 'new_size' is the same as 'old_size', return 'ptr' as is. */
    if (new_size == old_size)
        return ptr;

    /* Allocate a new block of 'new_size', copy data, and free the old block. */
    p = malloc(new_size);
    if (!p)
        return NULL;

    copy_size = new_size < old_size ? new_size : old_size;
    while (copy_size--)
        p[copy_size] = ((char *)ptr)[copy_size];
    free(ptr);
    return p;
}
