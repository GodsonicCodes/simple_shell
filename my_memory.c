#include "shell.h"




/* 
 * bfree - Deallocate memory and set the pointer to NULL.
 * @ptr: Address of the pointer to deallocate.
 *
 * This function frees the memory pointed to by 'ptr' and then sets 'ptr' to NULL.
 *
 * Return: 1 if memory was freed, otherwise 0.
 */





/*function bfree*/
int bfree(void **ptr)
{
    if (ptr && *ptr)
    {
        free(*ptr);      /* Free the memory pointed to by 'ptr'. */
        *ptr = NULL;     /* Set 'ptr' to NULL to avoid a dangling pointer. */
        return (1);      /* Memory deallocated successfully. */
    }
    return (0);          /* No memory to deallocate. */
}

