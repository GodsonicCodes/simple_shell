#include "shell.h"





/**
 * _realloc - Reallocates a block of memory.
 * @ptr: Pointer to the previous malloc'ated block.
 * @new_size: Byte size of the new block.
 * Return: Pointer to the old block or a new one if reallocated.
 */





/*function _realloc*/
void *_realloc(void *ptr, unsigned int new_size)
{
    /* If 'ptr' is NULL, simply allocate a new block of 'new_size'. */
    if (!ptr)
        return malloc(new_size);

    /* If 'new_size' is zero, free the previous block and return NULL. */
    if (!new_size)
    {
        free(ptr);
        return NULL;
    }

    /* Allocate a new block of 'new_size', copy data, and free the old block. */
    void *new_ptr = malloc(new_size);
    if (!new_ptr)
        return NULL;

    /* Calculate the smaller of the old and new sizes. */
    unsigned int copy_size = new_size < old_size ? new_size : old_size;

    memcpy(new_ptr, ptr, copy_size);
    free(ptr);
    return new_ptr;
}
